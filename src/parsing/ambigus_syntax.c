/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambigus_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:45:16 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/15 02:41:18 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	get_value(const char *str, size_t *i)
{
	char	*name;
	char	*value;
	char	*tmp;

	(*i)++;
	name = get_name(str, *i);
	if (!name)
		return (1);
	value = env_get_value(name);
	if (!value)
	{
		tmp = ft_strjoin("$", name);
		printf("minishell: %s: ambiguous redirect\n", tmp);
		free(tmp);
		free(name);
		return (-1);
	}
	return (free(name), 1);
}

static bool	after_redir(const char *str, size_t end)
{
	size_t	i;
	char	quote;
	bool	after;

	quote = 0;
	i = 0;
	after = false;
	while (i < end)
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		if (!quote && (str[i] == '<' || str[i] == '>'))
		{
			if (str[i] == '<' || str[i + 1] == '<')
				i++;
			else
				after = true;
		}
		i++;
	}
	return (after);
}

bool	ambigus_syntax(const char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		if (!quote && str[i] == '$' && after_redir(str, i))
		{
			if (get_value(str, &i) == -1)
				return (true);
		}
		i++;
	}
	return (false);
}
