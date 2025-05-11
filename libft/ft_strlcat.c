/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:13:40 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/29 00:14:13 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_lenght;
	size_t	src_lenght;
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	dest_lenght = ft_strlen(dest);
	src_lenght = ft_strlen(src);
	i = 0;
	if (dest_lenght >= size)
		return (src_lenght + size);
	while (src[i] && i < size - dest_lenght - 1)
	{
		dest[dest_lenght + i] = src[i];
		i++;
	}
	dest[i + dest_lenght] = '\0';
	return (dest_lenght + src_lenght);
}