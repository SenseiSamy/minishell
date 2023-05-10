/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 21:20:30 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/10 19:05:19 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	syntax_error(char *str)
{
	ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n", str);
	free(str);
	return (1);
}

int	pipe_syntax(const char *str, size_t *i)
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

int	redir_syntax(const char *str, size_t *i)
{
	char	*buff;
	char	tmp;

	buff = ft_calloc(3, sizeof(char));
	tmp = str[*i];
	if (str[*i + 1] == tmp)
		(*i)++;
	(*i)++;
	if (is_end(str, *i))
		return (free(buff), syntax_error(ft_strdup("newline")));
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
			return (free(buff), syntax_error(ft_strdup("||")));
		return (free(buff), syntax_error(ft_strdup("|")));
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

int	syntax_check(const char *str)
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
			return (1);
	}
	return (0);
}
