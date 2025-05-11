# include "../includes/minishell.h"
# include "../includes/libft.h"
# include "../includes/tokenizer.h"

int is_dir(char *path)
{
    struct stat buf;
    if (stat(path,&buf) == 0)
        return (S_ISDIR(buf.st_mode));
    return 0;
}

void print_error(char *name,char *error)
{
    ft_putstr_fd(name, 2);
    ft_putstr_fd(error ,2);
    ft_putchar_fd('\n',2);
}

int execute_cmd(t_execution *list,char *cmd)
{
        if (ft_redirection(list->file) == 1)
            exit(1);
        else
            execve(cmd,list->args,listToArray());
        exit(1);
}

void scan_cmd(t_execution *list)
{
    if (is_dir(list->args[0]))
    {
        g_status()->status = 126;
        print_error(list->args[0],": Is a directory");
    }
    else if (access(list->args[0],X_OK | F_OK) == 0)
        execute_cmd(list,list->args[0]);
    perror(list->args[0]);
    g_status()->status = 1;
    exit(1);

}

int is_valid(t_execution *list,char **path)
{
    int i = 0;
    char *tmp;
    char *full_cmd;
    while(path[i])
    {
        tmp = ft_strjoin(path[i], "/");
        full_cmd = ft_strjoin(tmp, list->args[0]);
        free(tmp);
        if (access(full_cmd,X_OK) == 0)
            return (execute_cmd(list,full_cmd));
        i++;
    }
    return (1);
}
void check_command_type(t_execution *list)
{
    int size;
    size = ft_lstsize(list);
    ft_execution(list,size);
}
void cmdWpath(t_execution *list, char **path)
{
    if (ft_strchr(list->args[0], '/'))
        scan_cmd(list);
    else if (is_dir(list->args[0]))
    {
        g_status()->status = 126;
        print_error(list->args[0], ": Is a directory");
        exit(126);
    }
    else if (is_valid(list, path) == 1)
    {
        g_status()->status = 127;
        print_error(list->args[0], ": command not found");
        exit(127);
    }
}
void execute_pipeCmd(t_execution *list, t_hr hr)
{
    if (hr.path)
        cmdWpath(list, hr.path);
    else
        scan_cmd(list);
}
void setup_pipes(t_hr hr, int size)
{
    if (hr.i > 0)
    {
        dup2(hr.pipes[(hr.i + 1) % 2][0], STDIN_FILENO);
        close(hr.pipes[(hr.i + 1) % 2][0]);
        close(hr.pipes[(hr.i + 1) % 2][1]);
    }
    if (hr.i < size - 1)
    {
        dup2(hr.pipes[hr.i % 2][1], STDOUT_FILENO); 
        close(hr.pipes[hr.i % 2][1]); 
        close(hr.pipes[hr.i % 2][0]);
    }
    
}
void wait_all(pid_t *pids,t_hr hr)
{
    int j = 0;
    int status = 0;
    while(j < hr.i)
    {
        waitpid(pids[j],&status,0);
        j++;
    }
    g_status()->status = WEXITSTATUS(status);
}
void execute_pipeline(t_execution *list, t_hr helper, int size)
{
    setup_pipes(helper, size);
    execute_pipeCmd(list, helper);
    // if (helper.i > 0)
    // {
    //     close(helper.pipes[(helper.i + 1) % 2][0]);
    //     close(helper.pipes[(helper.i + 1) % 2][1]);
    // }
    exit(1);
}
void ft_execution(t_execution *list,int size)
{
    t_hr hr;
    hr.i = 0;
    hr.path = get_path();
    pid_t *pid = malloc(sizeof(pid_t) * size);
    while(hr.i < size)
    {   
        if (hr.i < size - 1)
                pipe(hr.pipes[hr.i % 2]);
        pid[hr.i] = fork();
        if (pid[hr.i] == 0)
        {
            if (size == 1)
            {
                if (hr.path)
                    cmdWpath(list,hr.path);
                else
                    scan_cmd(list);
            }
            else
                execute_pipeline(list,hr,size);
            exit(EXIT_FAILURE);
        }
        if (hr.i < size - 1)
        {
            // close(hr.pipes[hr.i % 2][0]);        
            close(hr.pipes[hr.i % 2][1]);
        }
        if (hr.i > 0)
        {
            // close(hr.pipes[(hr.i + 1) % 2][1]);
            close(hr.pipes[(hr.i + 1) % 2][0]);
        }
        hr.i++;
        list = list->next;
    }
    wait_all(pid,hr);
    free(pid);
}

// void execute_single(t_execution *list,t_helper helper)
// {
//     if (hr.path)
//         cmdWpath(list, hr.path);
//     else
//         scan_cmd(list);
//     exit(1);
// }
// void execute_command(t_execution *list, t_helper helper, int size)
// {
//     if (size == 1)
//         execute_single(list,helper);
//     else
//         execute_pipeline(list, helper, size);
// }