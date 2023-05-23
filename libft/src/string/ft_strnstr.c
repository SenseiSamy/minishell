/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:36:35 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/21 03:16:52 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	little_len = 0;
	while (little[little_len])
		++little_len;
	if (!little_len)
		return ((char *)big);
	while (*big && len >= little_len)
	{
		if (*big == *little && !ft_memcmp(big, little, little_len))
			return ((char *)big);
		++big;
		--len;
	}
	return (NULL);
}
