/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:49:01 by sfyn              #+#    #+#             */
/*   Updated: 2025/05/16 12:53:29 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

int	check_quotes(char *input)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (input[i])
	{
		if (input[i] == '\'' && in_double == 0)
		{
			if (in_single == 0)
				in_single = 1;
			else
				in_single = 0;
		}
		else if (input[i] == '\"' && in_single == 0)
		{
			if (in_double == 0)
				in_double = 1;
			else
				in_double = 0;
		}
		i++;
	}
	if (in_single || in_double)
	{
		g_status()->status = 2;
		return (1);
	}
	return (0);
}

int	parser(t_token *tokens)
{
	t_token	*iterate;

	iterate = tokens;
	while (iterate)
	{
		if (iterate->type == PIPE)
		{
			if (!iterate->next || iterate->next->type == PIPE)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
				g_status()->status = 2;
				return (1);
			}
		}
		else if (iterate->type == HERE_DOC)
		{
			if (!iterate->next || iterate->next->type != DELIMITER)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
				g_status()->status = 2;
				return (1);
			}
		}
		else if (iterate->type == RED_IN || iterate->type == RED_OUT || iterate->type == APPEND)
		{
			if (!iterate->next || iterate->next->type != FILE_NAME)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
				g_status()->status = 2;
				return (1);
			}
		}
		iterate = iterate->next;
	}
	return (0);
}


int	check_parenthis(char *input)
{
	int	i;
	int	open_parenthis;

	i = 0;
	open_parenthis = 0;
	while (input[i])
	{
		if (input[i] == ')' && open_parenthis == 0)
		{
			ft_putstr_fd("minishell: parse error near `)'\n", 2);
			return (1);
		}
		else if (input[i] == '(' && open_parenthis == 0)
		{
			i++;
			open_parenthis = 1;
			while (input[i] && input[i] != ')')
			{
				if (input[i] == '(')
				{
					ft_putstr_fd("minishell: parse error near `('\n", 2);
					return (1);
				}
				i++;
			}
			if (input[i] == ')' && input[i - 1] == '(')
			{
				ft_putstr_fd("minishell : (empty subshell)\n", 2);
				return (1);
			}
			else if (input[i] == ')')
				open_parenthis = 0;
		}
		i++;
	}
	if (input[i] == '\0' && open_parenthis == 1)
	{
		ft_putstr_fd("minishell : unclosed subshell `('\n", 2);
		return (1);
	}
	return (0);
}

int	count_words(t_token *tokens)
{
	t_token	*iterator;
	int		i;

	iterator = tokens;
	i = 0;
	while (iterator)
	{
		if (iterator->type == PIPE)
			break ;
		i++;
		iterator = iterator->next;
	}
	return (i);
}

t_execution	*create_element(t_token *tokens)
{
	t_execution	*element;
	int			i;

	element = malloc(sizeof(t_execution));
	if (!element)
		return (NULL);
	element->args = malloc(sizeof(char *) * (count_words(tokens) + 1));
	if (!element->args)
	{
		free(element);
		return (NULL);
	}
	i = 0;
	while (i <= count_words(tokens))
		element->args[i++] = NULL;
	element->infile = -2;
	element->outfile = -2;
	element->file = NULL;
	element->next = NULL;
	return (element);
}
