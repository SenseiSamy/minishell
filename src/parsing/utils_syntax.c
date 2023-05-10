/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:53:07 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/10 18:53:20 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_end(const char *str, size_t i)
{
	while (ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (true);
	return (false);
}

bool	is_start(const char *str, size_t *i)
{
	while (ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '|')
		return (true);
	return (false);
}
