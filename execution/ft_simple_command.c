#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/tokenizer.h"

int ft_open(char *file_name, int flag)
{
	int fd;
	fd = open(file_name, flag, 0644);
	return (fd);
}
int ft_redirection(t_file *file)
{
	int fd;
	while (file)
	{
		if (file->infile)
		{
			fd = ft_open(file->file_name, O_RDONLY);
			if (fd == -1)
			{
				write(2, file->file_name, ft_strlen(file->file_name));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				g_status()->status = 1;
				return (1);
			}
			dup2(fd, 0);
			close(fd);
		}
		if (file->outfile)
		{
			fd = ft_open(file->file_name, O_CREAT | O_TRUNC | O_WRONLY);
			if (fd == -1)
			{
				write(2, file->file_name, ft_strlen(file->file_name));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				g_status()->status = 1;
				return (1);
			}
			dup2(fd, 1);
			close(fd);
		}
		if (file->append)
		{
			fd = ft_open(file->file_name, O_APPEND | O_CREAT | O_WRONLY);
			if (fd == -1)
			{
				write(2, file->file_name, ft_strlen(file->file_name));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				g_status()->status = 1;
				return (1);
			}
			dup2(fd, 1);
			close(fd);
		}
		file = file->next;
	}
	return (0);
}
// void execute_simple_cmnd(char **path, t_execution *list, int size)
// {
	// char *temp;
	// char *full_cmd;
	// (void)path;
	// char **envp;
	// int i = 0;
	// (void)size;
	// envp = listToArray();

	// while (path[i])
	// {
	// 	if (ft_redirection(list->file) == 1)
	// 		exit(1);
	// 	if (if_builtin(list->args[0]) != 0)
	// 	{
	// 		if (list->file)
	// 		{
	// 			if (ft_redirection(list->file) == 0)
	// 				is_builtin(list->args[0], list, size);
	// 		}
	// 		else
	// 		{
	// 			is_builtin(list->args[0], list, size);
	// 			exit(0);
	// 		}
	// 	}
	// 	else if (ft_strchr(list->args[0],'/'))
	// 	{
	// 		return (ft_free(path), execve(list->args[0], list->args, envp),
	// 				ft_free(list->args), exit(1));
	// 	}
	// 	if (access(full_cmd, X_OK) == 0)
	// 	{
	// 		ft_free(path);
	// 		if (list->infile != -2)
	// 			dup2(list->infile, 0);
	// 		if (list->outfile != -2)
	// 			dup2(list->outfile, 1);
	// 		if (execve(full_cmd, list->args, envp))
	// 			return (free(full_cmd), exit(1));
	// 	}
	// 	free(full_cmd);
	// 	i++;
	// }
	//execve(list->args[0],list->args,envp);
	// write(2, list->args[0], ft_strlen(list->args[0]));
	// write(2, " : command not found\n", 22);
	// return (ft_free(path), ft_free(list->args), exit(127));
// }

int ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
char **get_path()
{
	char *path;
	path = searchAndsave("PATH");
	if (path)
		return (ft_split(path, ':'));
	return (NULL);
}
