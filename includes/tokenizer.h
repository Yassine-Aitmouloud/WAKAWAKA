/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:56:13 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/09 13:11:08 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "minishell.h"
#include <fcntl.h>
t_token *tokenizer(char *input, t_token *tokens);
int check_quotes(char *input);
int check_parenthis(char *input);
t_token *lexer(t_token *list);
int parser(char *input);
int count_words(t_token *tokens);
void	ft_lstclear_v2(t_execution **lst);
#endif