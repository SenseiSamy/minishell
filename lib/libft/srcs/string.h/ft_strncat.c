/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:28:03 by cfrancie          #+#    #+#             */
/*   Updated: 2023/02/12 17:25:43 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*tmp;

	tmp = dest;
	while (*dest)
		dest++;
	while (n--)
		*dest++ = *src++;
	*dest = '\0';
	return (tmp);
}
