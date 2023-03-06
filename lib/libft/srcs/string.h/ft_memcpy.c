/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:27:00 by cfrancie          #+#    #+#             */
/*   Updated: 2023/01/04 18:19:19 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*ptr_src;
	char		*ptr_dest;

	if (!dest && !src)
		return (NULL);
	ptr_src = src;
	ptr_dest = dest;
	while (n--)
		*ptr_dest++ = *ptr_src++;
	return (dest);
}
