/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:01:03 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/20 17:36:56 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!joined)
		return (NULL);
	ft_memcpy(joined, s1, len_s1);
	ft_memcpy(joined + len_s1, s2, len_s2 + 1);
	return (joined);
}
