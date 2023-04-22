/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:27:00 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/23 00:00:21 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*srce;
	size_t				i;

	dst = (unsigned char *)dest;
	srce = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst[i] = srce[i];
		i++;
	}
	return (dest);
}
