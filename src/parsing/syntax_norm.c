/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:12:25 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/12 18:46:30 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
