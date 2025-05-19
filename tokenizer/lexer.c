/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:47:59 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/16 22:04:45 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

void	check_in(t_token *token)
{
	if (!ft_strncmp(token->token, "<", ft_strlen(token->token)))
	{
		token->type = RED_IN;
		if (token->next)
		{
			token = token->next;
			if (!check_if_operator(token))
				token->type = FILE_NAME;
		}
	}
	else if (!ft_strncmp(token->token, "<<", ft_strlen(token->token)))
	{
		token->type = HERE_DOC;
		if (token->next)
		{
			token = token->next;
			if (!check_if_operator(token))
				token->type = DELIMITER;
		}
	}
}

void	check_operator(t_token *token)
{
	if (!ft_strncmp(token->token, "|", ft_strlen(token->token)))
		token->type = PIPE;
	else if (!ft_strncmp(token->token, ">>", 2))
	{
		token->type = APPEND;
		if (token->next)
		{
			token = token->next;
			if (!check_if_operator(token))
				token->type = FILE_NAME;
		}
	}
	else if (!ft_strncmp(token->token, ">", 1))
	{
		token->type = RED_OUT;
		if (token->next)
		{
			token = token->next;
			if (!check_if_operator(token))
				token->type = FILE_NAME;
		}
	}
	else
		check_in(token);
}

void	check_argument(t_token *iteration)
{
	while (iteration != NULL && !check_opperator(iteration->token))
	{
		if (!check_if_operator(iteration))
			iteration->type = ARGUMENT;
		iteration = iteration->next;
	}
}

int	check_if_builtin(t_token *token)
{
	if (!ft_strncmp(token->token, "echo", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, "cd", 2))
		return (1);
	else if (!ft_strncmp(token->token, "pwd", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, "export", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, "unset", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, "env", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, "exit", ft_strlen(token->token)))
		return (1);
	return (0);
}

t_token	*lexer(t_token *list)
{
	int		new_cmd = 1;
	t_token	*iterate = list;

	while (iterate != NULL)
	{
		if (iterate->type != TEST)
		{
			iterate = iterate->next;
			continue;
		}
		if (new_cmd && check_if_builtin(iterate))
		{
			iterate->type = BUILTIN;
			check_argument(iterate->next);
			new_cmd = 0;
		}
		else if (check_if_operator(iterate))
		{
			check_operator(iterate);
			if (iterate->type == PIPE)
				new_cmd = 1;
		}
		else
		{
			iterate->type = WORD;
			new_cmd = 0;
		}
		iterate = iterate->next;
	}
	return (list);
}
