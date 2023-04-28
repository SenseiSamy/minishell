/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:13:06 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/28 20:13:38 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	count_pipe(const char *str)
{
	size_t	i;
	size_t	count;
	char	quote;

	i = 0;
	count = 1;
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
