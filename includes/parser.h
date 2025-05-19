/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:37:06 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/14 22:45:29 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "minishell.h"

t_execution	*pre_execution(t_token *tokens);
void	ft_lstadd_back_v2(t_execution **lst, t_execution *new);
t_execution	*ft_lstlast_v2(t_execution *lst);
t_token	*copy_elements(t_execution *exec, t_token *iterate, t_token *tokens,
		t_execution *exec_list);
t_token	*handle_redirection(t_execution *exec, t_token *iterate,
		t_token *tokens, t_execution *exec_list);
void	parse_file(t_norm *norm, int flag);
t_execution	*create_element(t_token *tokens);
void	parse_file(t_norm *norm, int flag);
void	init_and_add_file(t_norm *norm, t_file **element, int type);
t_file	*create_element_file(char *filename);
t_file	*ft_lstlast_v3(t_file *lst);
void	ft_lstadd_back_v3(t_file **lst, t_file *new);
#endif
