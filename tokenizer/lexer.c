/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:47:59 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/30 13:31:00 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

int	check_if_operator(t_token *token)
{
	if (!ft_strncmp(token->token, "|", ft_strlen(token->token)))
	return (1);
	else if (!ft_strncmp(token->token, ">>", ft_strlen(token->token)))
	return (1);
	else if (!ft_strncmp(token->token, "<", ft_strlen(token->token)))
	return (1);
	else if (!ft_strncmp(token->token, "<<", ft_strlen(token->token)))
	return (1);
	else if (!ft_strncmp(token->token, ">", ft_strlen(token->token)))
	return (1);
	return (0);
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
			token->type = FILE_NAME;
		}
	}
	else if (!ft_strncmp(token->token, ">", 1))
	{
		token->type = RED_OUT;
		if (token->next)
		{
			token = token->next;
			token->type = FILE_NAME;
		}
	}
	else if (!ft_strncmp(token->token, "<", ft_strlen(token->token)))
	{
		token->type = RED_IN;
		if (token->next)
		{
			token = token->next;
			token->type = FILE_NAME;
		}
	}
	else if (!ft_strncmp(token->token, "<<", ft_strlen(token->token)))
	{
		token->type = HERE_DOC;
		if (token->next)
		{ 
			token = token->next;
			token->type = DELIMITER;
		}
	}
}
int	check_opperator(char *token)
{
	if (!ft_strncmp(token, "|", ft_strlen(token)))
		return (1);
	return (0);
}

void	check_argument(t_token *iteration)
{
	while (iteration != NULL && !check_opperator(iteration->token))
	{
		if (!check_if_operator(iteration))
		{
			iteration->type = ARGUMENT;
			iteration = iteration->next;
		}
		else 
		{
			check_operator(iteration);
			break;
		}
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
	t_token	*iterate;

	iterate = list;
	while (iterate != NULL)
	{
if (check_if_builtin(iterate))
{
	iterate->type = BUILTIN;
	check_argument(iterate->next);
}
		else if (check_if_operator(iterate))
		{
			check_operator(iterate);
		}
		else if (iterate->type == TEST)
		{
			iterate->type = WORD;
		}
		iterate = iterate->next;
	}
	return list;
}