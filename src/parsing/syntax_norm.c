/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:12:25 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/15 00:04:10 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_empty(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!isspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	syntax_error(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	free(str);
	return (true);
}

bool	is_end(const char *str, size_t i)
{
	while (isspace(str[i]))
		i++;
	return (!str[i]);
}

bool	is_start(const char *str, size_t *i)
{
	while (isspace(str[*i]))
		(*i)++;
	return (str[*i] == '|');
}
