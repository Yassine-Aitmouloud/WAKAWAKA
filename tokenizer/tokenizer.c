/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 02:20:32 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/02 09:39:39 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

#include "../includes/tokenizer.h"

int	is_space_or_operator(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

t_token	*tokenizer(char *input, t_token *tokens)
{
	int		i = 0;
	int		j;
	t_token	*element;
	t_token	*test;

	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i])
			break;
		if (!is_space_or_operator(input[i]))
		{
			j = i;
			while (input[i] && !is_space_or_operator(input[i]))
			{
				if (input[i] == '"')
				{
					i++;
					while (input[i] && input[i] != '"')
						i++;
					if (input[i])
						i++;
				}
				else if (input[i] == '\'')
				{
					i++;
					while (input[i] && input[i] != '\'')
						i++;
					if (input[i])
						i++;
				}
				else
					i++;
			}
			element = new_element(ft_strndup(&input[j], i - j));
			ft_lstadd_back(&tokens, element);
		}
		else if (input[i] == '(')
		{
			j = i;
			i++;
			while (input[i] && input[i] != ')')
				i++;
			if (input[i])
				i++;
			element = new_element(ft_strndup(&input[j], i - j));
			ft_lstadd_back(&tokens, element);
		}
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>'
			|| input[i] == '&')
		{
			if ((input[i] == '<' && input[i + 1] == '<') ||
				(input[i] == '>' && input[i + 1] == '>') ||
				(input[i] == '|' && input[i + 1] == '|') ||
				(input[i] == '&' && input[i + 1] == '&'))
			{
				element = new_element(ft_strndup(&input[i], 2));
				i += 2;
			}
			else
			{
				element = new_element(ft_strndup(&input[i], 1));
				i++;
			}
			ft_lstadd_back(&tokens, element);
		}
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
