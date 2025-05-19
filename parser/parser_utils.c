/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:38:14 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/14 22:44:15 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_file	*create_element_file(char *filename)
{
	t_file	*element;

	(void)filename;
	element = malloc(sizeof(t_file));
	element->infile = 0;
	element->file_name = NULL;
	element->outfile = 0;
	element->append = 0;
	element->heredoc = 0;
	element->next = NULL;
	return (element);
}

t_file	*ft_lstlast_v3(t_file *lst)
{
	t_file	*last_content;

	if (!lst)
		return (NULL);
	last_content = lst;
	while (last_content != NULL && last_content->next != NULL)
	{
		last_content = last_content->next;
	}
	return (last_content);
}

void	ft_lstadd_back_v3(t_file **lst, t_file *new)
{
	t_file	*last;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast_v3(*lst);
		last->next = new;
	}
}

t_execution	*ft_lstlast_v2(t_execution *lst)
{
	t_execution	*last_content;

	if (!lst)
		return (NULL);
	last_content = lst;
	while (last_content != NULL && last_content->next != NULL)
	{
		last_content = last_content->next;
	}
	return (last_content);
}

void	ft_lstadd_back_v2(t_execution **lst, t_execution *new)
{
	t_execution	*last;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast_v2(*lst);
		last->next = new;
	}
}
