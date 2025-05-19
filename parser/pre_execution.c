/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:35:50 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/19 19:18:13 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	init_and_add_file(t_norm *norm, t_file **element, int type)
{
	*element = create_element_file(norm->token->token);
	(*element)->file_name = ft_strndup(norm->token->token,
			ft_strlen(norm->token->token));
	if (type == RED_IN)
		(*element)->infile = 1;
	else if (type == RED_OUT)
		(*element)->outfile = 1;
	else if (type == APPEND)
		(*element)->append = 1;
	ft_lstadd_back_v3(&norm->ex->file, *element);
}

void	parse_file(t_norm *norm, int flag)
{
	t_file	*element;

	element = NULL;
	if (flag == RED_IN)
		init_and_add_file(norm, &element, RED_IN);
	else if (flag == RED_OUT)
		init_and_add_file(norm, &element, RED_OUT);
	else if (flag == APPEND)
		init_and_add_file(norm, &element, APPEND);
}

t_token	*handle_redirection(t_execution *exec, t_token *iterate,
		t_token *tokens, t_execution *exec_list)
{
	int		flag;
	t_norm	norm;

	flag = iterate->type;
	iterate = iterate->next;
	if (!iterate)
		return (NULL);
	norm.ex = exec;
	norm.exec_list = exec_list;
	norm.tokens = tokens;
	norm.token = iterate;
	parse_file(&norm, flag);
	return (iterate->next);
}

t_token	*copy_elements(t_execution *exec, t_token *iterate, t_token *tokens,
		t_execution *exec_list)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (iterate)
	{
		if (iterate->type == PIPE)
			break ;
		if (iterate->type == RED_IN || iterate->type == RED_OUT
			|| iterate->type == HERE_DOC || iterate->type == APPEND)
		{
			iterate = handle_redirection(exec, iterate, tokens, exec_list);
			continue ;
		}
		if (iterate && iterate->token)
			exec->args[i++] = ft_strndup(iterate->token,
					ft_strlen(iterate->token));
		iterate = iterate->next;
	}
	exec->args[i] = NULL;
	return (iterate);
}

t_execution	*pre_execution(t_token *tokens)
{
	t_execution	*exec_list;
	t_execution	*temp;
	t_token		*iterate;

	exec_list = NULL;
	temp = NULL;
	iterate = tokens;
	while (iterate)
	{
		if (iterate->type == PIPE)
			iterate = iterate->next;
		temp = create_element(iterate);
		iterate = copy_elements(temp, iterate, tokens, exec_list);
		ft_lstadd_back_v2(&exec_list, temp);
	}
	return (exec_list);
}
