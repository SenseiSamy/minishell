/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:36:16 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/24 03:41:02 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_dest;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	size_dest = ft_strlen(dst);
	while (i < size && dst[i])
		i++;
	if (i == size)
		return (ft_strlen(src) + i);
	while (i < size - 1 && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (size_dest + ft_strlen(src));
}
