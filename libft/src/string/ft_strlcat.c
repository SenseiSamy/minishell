/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:36:16 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/21 03:16:35 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;

	i = 0;
	while (dst[i] && i < size)
		++i;
	dst_len = i;
	while (src[i - dst_len] && i + 1 < size)
	{
		dst[i] = src[i - dst_len];
		++i;
	}
	if (dst_len < size)
		dst[i] = '\0';
	while (src[i - dst_len])
		++i;
	return (i);
}
