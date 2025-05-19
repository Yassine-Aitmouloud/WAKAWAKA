/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmnds2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:56 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/16 22:14:23 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

void	scan_cmd(t_execution *list)
{
	if (is_dir(list->args[0]))
	{
		g_status()->status = 126;
		print_error(list->args[0], ": Is a directory");
		ft_freeEnvp();
		exit(g_status()->status);
	}
	else if (access(list->args[0], X_OK | F_OK) == 0)
		execute_cmd(list, list->args[0]);
	else
		perror(list->args[0]);
	g_status()->status = 127;
	ft_freeEnvp();
	exit(g_status()->status);
}