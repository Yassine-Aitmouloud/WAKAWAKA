/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:09 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/19 18:57:24 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "tokenizer.h"

int	is_dir(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == 0)
		return (S_ISDIR(buf.st_mode));
	return (0);
}

void	print_error(char *name, char *error)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(error, 2);
	ft_putchar_fd('\n', 2);
}

void	check_command_type(t_execution *list)
{
	int	size;
	size = ft_lstsize(list);
	ft_execution(list, size);
}

void	no_args(t_execution *list)
{
	pid_t pid;
	pid = fork();
	if (pid == 0)
		exit(ft_redirection(list->file));
	waitpid(pid,&g_status()->status,0);
}

void	ft_execution(t_execution *list, int size)
{
	t_hr	hr;
	int		pipes[2][2];
	pid_t	*pid;

	hr.i = 0;
	pid = malloc(sizeof(pid_t) * size);
	while (hr.i < size)
	{
		if (if_builtin(list->args[0]) != 0 && size == 1)
		{
			check_builtin(list, size);
			break ;
		}
		if (hr.i < size - 1)
			pipe(pipes[hr.i % 2]);
		pid[hr.i] = fork();
		if (pid[hr.i] == 0)
		{
			sig_child();
			execute_commands(list, hr, pipes, size);
		}
		close_previous(pipes, hr.i);
		hr.i++;
		list = list->next;
	}
	cleanup(pid, hr);
}
