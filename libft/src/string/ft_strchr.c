/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:36:09 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/24 14:37:35 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	tmp;

	tmp = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == tmp)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == tmp)
		return ((char *)s + i);
	return (NULL);
}
