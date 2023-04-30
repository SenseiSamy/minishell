/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:13:06 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/30 01:09:40 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	on_quote(const char *str, size_t i_str)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i] && i < i_str)
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = '\0';
		i++;
	}
	if (quote)
		return (true);
	return (false);
}

size_t	count_pipe(const char *str)
{
	size_t	i;
	size_t	count;
	char	quote;

	i = 0;
	count = 0;
	quote = '\0';
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = '\0';
		else if (!quote && str[i] == '|')
			count++;
		i++;
	}
	return (count);
}
