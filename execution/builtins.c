/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:23 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/19 15:19:24 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

void	ft_env(void)
{
	t_envp	*tmp;

	tmp = g_new_envp;
	while (tmp)
	{
		if (tmp->key && tmp->value != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_export(t_execution *list)
{
	int		i;
	t_envp	*node;
	t_envp	*export;

	i = 1;
	export = g_new_envp;
	while (list->args[i])
	{
		if (check_sen(list->args[i]) == 0)
		{
			print_error("bash: export:" ,list->args[i]);
			write(2,": not a valid identifier\n",25);
			g_status()->status = 1;
			i++;
		}
		else if (already_in(list->args[i]) == 1)
			i++;
		else
		{
			node = new_element2(list->args[i]);
			ft_lstadd_back2(&g_new_envp, node);
			i++;
		}
	}
	if (!list->args[1])
	{
		while (export)
		{
			if (export->key && export->value)
				printf("declare -x %s=\"%s\"\n", export->key, export->value);
			else if (export->key)
				printf("declare -x %s\n", export->key);
			export = export->next;
		}
	}
}

void	ft_unset(t_execution *list)
{
	t_envp	*prev;
	t_envp	*current;

	prev = NULL;
	int(i) = 1;
	while (list->args[i])
	{
		current = g_new_envp;
		prev = NULL;
		while (current)
		{
			if (!ft_strncmp(list->args[i], current->key,
					ft_strlen(list->args[i]))
				&& current->key[ft_strlen(list->args[i])] == '\0')
			{
				if (prev == NULL)
					g_new_envp = current->next;
				else
					prev->next = current->next;
				free(current->key);
				free(current->value);
				free(current);
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
}

void	ft_exit(t_execution *input, int size)
{
	if (size == 1)
	{
		g_status()->status = 0;		
		write(2,"exit\n",5);
	}
	if (input->args[1] && checkifnum(input->args[1]) == 0)
	{
		print_error("bash: exit: ", input->args[1]);
		write(2,": numeric argument required\n",28);
		g_status()->status = 2;
	}
	else if (input->args[2])
	{
		write(2,"bash: exit: too many arguments\n",31);
		g_status()->status = 1;
	}
	else if (input->args[1])
		g_status()->status = ft_atoi(input->args[1]);
	else
		exit(g_status()->status);
}

void	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
		printf("%s\n", searchAndsave("PWD"));
	else
		printf("%s\n", buf);
	free(buf);
	g_status()->status = 0;
}
