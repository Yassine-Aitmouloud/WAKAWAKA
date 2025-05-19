/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 02:20:32 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/16 21:36:09 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

void	handle_quotes(char *input, int *i, int *j)
{
	*j = *i;
	while (input[*i] && !is_space_or_operator(input[*i]))
	{
		if (input[*i] == '"')
		{
			(*i)++;
			while (input[*i] && input[*i] != '"')
				(*i)++;
			if (input[*i])
				(*i)++;
		}
		else if (input[*i] == '\'')
		{
			(*i)++;
			while (input[*i] && input[*i] != '\'')
				(*i)++;
			if (input[*i])
				(*i)++;
		}
		else
			(*i)++;
	}
}

void	handle_parenthis(char *input, int *i, int *j)
{
	*j = *i;
	(*i)++;
	while (input[*i] && input[*i] != ')')
		(*i)++;
	if (input[*i])
		(*i)++;
}

void	handle_operators(char *input, t_token **element, t_token **tokens,
		int *i)
{
	if ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>'
			&& input[*i + 1] == '>'))
	{
		*element = new_element(ft_strndup(&input[*i], 2));
		*i += 2;
	}
	else
	{
		*element = new_element(ft_strndup(&input[*i], 1));
		(*i)++;
	}
	ft_lstadd_back(tokens, *element);
}

void	norm(char *input, t_token **element, t_token **tokens, int *i)
{
	int	j;

	j = 0;
	if (!is_space_or_operator(input[*i]))
	{
		handle_quotes(input, i, &j);
		*element = new_element(ft_strndup(&input[j], *i - j));
		ft_lstadd_back(tokens, *element);
	}
	else if (input[*i] == '(')
	{
		handle_parenthis(input, i, &j);
		*element = new_element(ft_strndup(&input[j], *i - j));
		ft_lstadd_back(tokens, *element);
	}
	else if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
		handle_operators(input, element, tokens, i);
}

t_token	*tokenizer(char *input, t_token *tokens)
{
	int		i;
	t_token	*element;
	t_token	*test;

	element = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i])
			break ;
		norm(input, &element, &tokens, &i);
	}
	test = tokens;
	while (test)
	{
		test->type = TEST;
		test = test->next;
	}
	tokens = lexer(tokens);
	return (tokens);
}
