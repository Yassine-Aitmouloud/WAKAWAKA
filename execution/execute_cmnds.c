/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmnds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:53 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/19 20:00:57 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

int	execute_cmd(t_execution *list, char *cmd)
{	
	if (list->args[0] == NULL && list->file != NULL)
	{
		no_args(list);
		exit(0);
	}
	if (ft_redirection(list->file) == 1)
		exit(1);
	else
		execve(cmd, list->args, listToArray());
	free(cmd);
	exit(127);
}

void	cmdWpath(t_execution *list, char **path, int size)
{
	(void)path;
	if (if_builtin(list->args[0]) != 0)
	{
		is_builtin(list->args[0], list, size);
		ft_freeEnvp();
		exit(g_status()->status);
	}
	else if (ft_strchr(list->args[0], '/'))
		scan_cmd(list);
	else if (is_dir(list->args[0]))
	{
		print_error(list->args[0], ": command not found");
		g_status()->status = 127;
		exit(127);
	}
	else if (is_valid(list) == 1)
	{
		g_status()->status = 127;
		print_error(list->args[0], ": command not found");
		ft_freeEnvp();
		exit(127);
	}
}

void	execute_Cmd(t_execution *list, t_hr hr, int size)
{
	if (search_in_env("PATH"))
		cmdWpath(list, hr.path, size);
	else
		scan_cmd(list);
}

void	execute_commands(t_execution *list, t_hr hr, int pipes[2][2], int size)
{
	if (list->args[hr.i] == NULL && list->file != NULL)
	{
		no_args(list);
		exit(0);
	}
	else if (size == 1)
		execute_Cmd(list, hr, size);
	else
		execute_pipeline(pipes, list, hr, size);
}

int	is_valid(t_execution *list)
{
	int		i;
	char	*tmp;
	char	*full_cmd;
	char	**paths;
	i = 0;
	if ( (list->args[0]== NULL) || (list->args[0][0] == '\0'))
		return 1;
	paths = get_path();
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_cmd = ft_strjoin(tmp, list->args[0]);
		free(tmp);
		if (access(full_cmd, X_OK) == 0)
			return (execute_cmd(list, full_cmd));
		free(full_cmd);
		i++;
	}
	ft_free(paths);
	return (1);
}
