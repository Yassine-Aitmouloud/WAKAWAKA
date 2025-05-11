# include "../includes/minishell.h"
# include "../includes/libft.h"
# include "../includes/tokenizer.h"

int count_pipe_line(t_execution *list)
{
    int count;
    count = 0;
    while(list && list->args)
    {
        count++;
        list = list->next;
    }
    return (count);
}

// void execute_pipes(char **path, t_execution *list,int size)
// {
//     int i = 0;
//     int pipes[2][2];
//     pid_t *pid = malloc(sizeof(pid_t) * size);
//     while(i < size)
//     {
//         if (list->args[i] == NULL && list->file != NULL)
//         {
//             int stdout_copy = dup(STDOUT_FILENO);
//             int stdin_copy = dup(STDIN_FILENO);
//             ft_redirection(list->file);  
//             dup2(stdout_copy,1);
//             dup2(stdin_copy,0);      
//             list = list->next;
//             i++;
//         }
//         else if (size == 1 && if_builtin(list->args[0]) != 0)
//         {
//             int stdout_copy = dup(1);
//             int stdin_copy = dup(0);
//             if (list->file)
//             {
//                 if (ft_redirection(list->file) == 0)
//                 {
//                     is_builtin(list->args[0], list,size);
//                     dup2(stdout_copy,1);
//                     dup2(stdin_copy,0);
//                 }
//             }
//             else
//             {
//                 is_builtin(list->args[0], list,size);
//                 dup2(stdout_copy,1);
//                 dup2(stdin_copy,0);
//             }
//             break;
//         }
//         else
//         {       
//             if (i < size - 1)
//                 pipe(pipes[i % 2]);
//             pid[i] = fork();
//             if (pid[i] == 0)
//             {
//                 if (i > 0)
//                 dup2(pipes[(i + 1) % 2][0], 0);
//                 if (i < size - 1)
//                 {
//                     dup2(pipes[i % 2][1], 1);
//                     close(pipes[i % 2][0]);
//                 }
//                 execute_simple_cmnd(path,list,size);
//             }
//             if (i > 0)
//                 close(pipes[(i + 1) % 2][0]);
//             if (i < size - 1)
//                 close(pipes[i % 2][1]);
//             i++;
//             list = list->next;
//         }
//     }
//     i = 0;
//     while(i < size)
//     {
//         waitpid(pid[i], &g_status()->status, 0);
//         // printf("%d\n",g_status()->status >> 8);
//         i++;
//     }
//     free(pid);
// }
