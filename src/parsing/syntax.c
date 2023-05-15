/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 02:35:21 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/15 03:04:57 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	pipe_syntax(const char *str, size_t *i)
{
	if (is_end(str, *i))
		return (syntax_error(ft_strdup("newline")));
	if (str[*i] == '|')
	{
		(*i)++;
		if (str[*i] == '|')
			return (syntax_error(ft_strdup("||")));
		while (ft_isspace(str[*i]))
			(*i)++;
		if (is_end(str, *i) || str[*i] == '|')
			return (syntax_error(ft_strdup("|")));
	}
	return (0);
}

static int	redir_norme(const char *str, size_t *i)
{
	char	*buff;

	buff = ft_calloc(3, sizeof(char));
	if (!buff)
		return (1);
	if (str[*i] == '>' || str[*i] == '<')
	{
		if (str[*i] == '<' && str[*i + 1] == '>')
			return (free(buff), syntax_error(ft_strdup("<>")));
		buff[0] = str[*i];
		if (str[*i] == str[*i + 1])
			buff[1] = str[(*i)++];
		return (syntax_error(buff));
	}
	return (free(buff), 0);
}

static int	redir_syntax(const char *str, size_t *i)
{
	if (str[*i] == str[*i + 1])
		(*i)++;
	(*i)++;
	while (ft_isspace(str[*i]))
		(*i)++;
	if (!str[*i])
		return (syntax_error(ft_strdup("newline")));
	if (redir_norme(str, i))
		return (1);
	if (str[*i] == '|')
	{
		if (str[*i + 1] == '|')
			return (syntax_error(ft_strdup("||")));
		return (syntax_error(ft_strdup("|")));
	}
	return (0);
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
			return (syntax_error(ft_strdup("||")));
		return (syntax_error(ft_strdup("|")));
	}
	while (i < ft_strlen(str))
	{
		if (ft_loop(str, &i, &quote))
			return (true);
	}
	return (false);
}
