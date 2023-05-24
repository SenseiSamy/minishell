/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:36:35 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/24 03:41:34 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	j = 0;
	while (big[i] && i < len)
	{
		while (big[i + j] && (big[i + j] == little[j]) && i + j < len)
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
		j = 0;
	}
	return (NULL);
}
