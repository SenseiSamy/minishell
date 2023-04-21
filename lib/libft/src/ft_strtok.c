/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:31:44 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/21 00:33:28 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_delim(char c, const char *delim)
{
	size_t	i;

	i = 0;
	while (delim[i] != '\0')
	{
		if (c == delim[i])
			return (true);
		i++;
	}
	return (false);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*save;
	char		*token;

	if (str != NULL)
		save = str;
	if (save == NULL)
		return (NULL);
	while (*save != '\0' && is_delim(*save, delim))
		save++;
	if (*save == '\0')
	{
		save = NULL;
		return (NULL);
	}
	token = save;
	while (*save != '\0' && !is_delim(*save, delim))
		save++;
	if (*save != '\0')
	{
		*save = '\0';
		save++;
	}
	else
		save = NULL;
	return (token);
}
