/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:13:29 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/20 17:33:55 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft.h"
#include <stdlib.h>

static size_t	get_size_array(char const *s, char c)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			size++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (size);
}

static size_t	size_next_word(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (s[size] != '\0' && s[size] != c)
		size++;
	return (size);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	j;

	if (s == NULL)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (get_size_array(s, c) + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		array[j] = ft_substr(s, i, size_next_word(&s[i], c));
		if (array[j] == NULL)
			return (NULL);
		j++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	array[j] = NULL;
	return (array);
}
