/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:56:13 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/16 08:29:37 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"
# include <fcntl.h>

t_token	*tokenizer(char *input, t_token *tokens);
int		check_quotes(char *input);
int		check_parenthis(char *input);
t_token	*lexer(t_token *list);
int		parser(t_token *tokens);
int		count_words(t_token *tokens);
void	ft_lstclear_v2(t_execution **lst);
int		is_space_or_operator(char c);
int		check_opperator(char *token);
int		check_if_operator(t_token *token);
#endif
