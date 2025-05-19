/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsUtils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:37 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/16 15:20:26 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

int	already_in(char *arg)
{
	t_envp	*tmp;
	char	*key;
	char	*new_value;
	int		len_key;
	int		append;

	tmp = g_new_envp;
	append = 0;
	len_key = CountLenKey(arg);
	if (arg[len_key] == '+' && arg[len_key + 1] == '=')
		append = 1;
	key = ft_strndup(arg, len_key);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, len_key) == 0 
			&& tmp->key[len_key] == '\0') 
		{
			if (append)
				new_value = ft_strjoin(tmp->value, arg + len_key + 2);
			else
				new_value = ft_strdup(arg + len_key + 1);
			free(tmp->value);
			tmp->value = new_value;
			free(key);
			return (1);
		}
		tmp = tmp->next;
	}
	free(key);
	return (0);
}
int	if_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
