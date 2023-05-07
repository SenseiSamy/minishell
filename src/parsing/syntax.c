/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 21:20:30 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/07 00:10:50 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected", 2);
	ft_putstr_fd(" token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	free(str);
	return (1);
}

static int	is_error(const char *str, int i)
{
	char	*error;

	while (str[i] && ft_isspace(str[i]))
		++i;
	if (!str[i])
		return (syntax_error(ft_strdup("newline")));
	error = ft_calloc(sizeof(char), 3);
	if (str[i] == '<' || str[i] == '>')
	{
		error[0] = str[i];
		if (str[i + 1] && (str[i + 1] == '<' || str[i + 1] == '>'))
		{
			error[1] = str[i + 1];
			return (syntax_error(error));
		}
		return (syntax_error(error));
	}
	free(error);
	return (0);
}

static int	syntax_utils(const char *str, size_t *i, char *quote)
{
	if (str[*i] == '\'' || str[*i] == '"')
		*quote = str[(*i)++];
	else if (*quote == '\0' && (str[*i] == '>' || str[*i] == '<'))
	{
		if (str[*i] == str[*i + 1])
			(*i)++;
		if (is_error(str, *i + 1))
			return (1);
	}
	else if (*quote == '\0' && str[*i] == '|')
	{
		while (str[*i] && ft_isspace(str[*i]))
			++(*i);
		if (!str[*i])
			return (syntax_error(ft_strdup("newline")));
	}
	return (0);
}

int	syntax_check(const char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	while (i < ft_strlen(str))
	{
		if (str[i] == quote)
		{
			quote = '\0';
			++i;
		}
		else
			if (syntax_utils(str, &i, &quote))
				return (1);
		++i;
	}
	return (0);
}
