/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:35:50 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/20 17:30:36 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n && *(unsigned char *)s != (unsigned char)c)
	{
		++s;
		--n;
	}
	if (n)
		return ((void *)s);
	return (NULL);
}
