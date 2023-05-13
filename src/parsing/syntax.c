/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 02:35:21 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/12 16:39:07 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	pipe_syntax(const char *str, size_t *i)
{
	if (is_end(str, *i))
		return (syntax_error(strdup("newline")));
	if (str[*i] == '|')
	{
		(*i)++;
		if (str[*i] == '|')
			return (syntax_error(strdup("||")));
		while (isspace(str[*i]))
			(*i)++;
		if (is_end(str, *i) || str[*i] == '|')
			return (syntax_error(strdup("|")));
	}
	return (0);
}

static int	redir_syntax(const char *str, size_t *i)
{
	char	*buff;
	char	tmp;

	buff = calloc(3, sizeof(char));
	tmp = str[*i];
	if (str[*i + 1] == tmp)
		(*i)++;
	(*i)++;
	if (is_end(str, *i))
		return (free(buff), syntax_error(strdup("newline")));
	if (str[*i] == '>' || str[*i] == '<')
	{
		buff[0] = str[*i];
		if (str[*i + 1] == '>' || str[*i + 1] == '<')
			buff[1] = str[++(*i)];
		return (syntax_error(buff));
	}
	else if (str[*i] == '|')
	{
		if (str[*i + 1] == '|')
			return (free(buff), syntax_error(strdup("||")));
		return (free(buff), syntax_error(strdup("|")));
	}
	return (free(buff), 0);
}

static int	ft_loop(const char *str, size_t *i, char *quote)
{
	if (!quote && (str[*i] == '"' || str[*i] == '\''))
		*quote = str[(*i)++];
	else if (*quote && str[*i] == *quote)
	{
		*quote = '\0';
		(*i)++;
	}
	else if (!*quote && str[*i] == '|' && pipe_syntax(str, i))
		return (1);
	else if (!*quote && (str[*i] == '>' || str[*i] == '<')
		&& redir_syntax(str, i))
		return (1);
	else
		(*i)++;
	return (0);
}

bool	syntax_check(const char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	if (is_start(str, &i))
	{
		if (str[i + 1] == '|')
			return (syntax_error(strdup("||")));
		return (syntax_error(strdup("|")));
	}
	while (i < strlen(str))
	{
		if (ft_loop(str, &i, &quote))
			return (true);
	}
	return (false);
}
