/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:27:58 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/11 14:03:36 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

int	is_space_or_operator(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

int	check_opperator(char *token)
{
	if (!ft_strncmp(token, "|", ft_strlen(token)))
		return (1);
	return (0);
}

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
