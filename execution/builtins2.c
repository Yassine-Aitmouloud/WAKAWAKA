/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:28 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/18 17:33:05 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

void	ft_chdir(t_execution *input)
{
	if (input->args[2])
	{
		print_error(input->args[0],": too many arguments");
		g_status()->status = 1;
	}
	else if (!input->args[1])
	{
		if (search_in_env("HOME") == 1)
		{
			change_in_env("OLDPWD", getcwd(NULL, 0));
			if (chdir(searchAndsave("HOME")))
			{
				g_status()->status = 0;
				return ;				
			}
			change_in_env("PWD", getcwd(NULL, 0));
			g_status()->status = 0;
		}
		else
		{
			printf("%s\n", "cd: HOME not set");
			g_status()->status = 1;
		}
	}
	else
	{
		change_in_env("OLDPWD", getcwd(NULL, 0));
		if (chdir(input->args[1]) == -1)
		{	
			g_status()->status = 1;
			print_error("bash: cd: " ,input->args[1]);
			write(2,":No such file or directory\n",25);
			return ;
		}
		change_in_env("PWD", getcwd(NULL, 0));
		g_status()->status = 0;
	}
	// g_status()->status = 0;
}

void	ft_echo(t_execution *input)
{
	int i = 1;
	int flag = 1;

	while (input->args[i] && strncmp(input->args[i], "-n", 2) == 0)
	{
		int j = 2;
		while (input->args[i][j] == 'n')
			j++;
		if (input->args[i][j] != '\0')
			break ;
		flag = 0;
		i++;
	}
	while (input->args[i])
	{
		ft_putstr_fd(input->args[i], 1);
		if (input->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (flag)
		ft_putchar_fd('\n', 1);
	g_status()->status = 0;
}