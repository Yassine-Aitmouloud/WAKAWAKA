/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 01:26:48 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/28 01:42:20 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_token	*new_element(char *ptr)
{
	t_token *new;
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = ptr;
	new->next = NULL;
	return (new);
}