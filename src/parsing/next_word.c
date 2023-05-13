/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:25:10 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/13 16:16:57 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	ft_issep(char c, char quote)
{
	if (!quote && ((c == '|' || c == '<' || c == '>') || isspace(c)))
		return (true);
	return (false);
}

static void	ft_loop(char *str, const char *line, size_t *il)
{
	char	quote;
	size_t	i;

	quote = 0;
	i = 0;
	while (line[*il] != '\0' && ft_issep(line[*il], quote) == false)
	{
		if (!quote && (line[*il] == '\'' || line[*il] == '"'))
			quote = line[*il];
		else if (quote && line[*il] == quote)
			quote = 0;
		else if (line[*il] == '$' && quote != '\'')
		{
			if (isspace(line[*il + 1])
				|| (!isalnum(line[*il + 1]) && line[*il + 1] != '_' && line[*il + 1] != '?'))
				str[i++] = '$';
			else
				convert_variable(line, il, str, &i);
		}
		else
			str[i++] = line[*il];
		(*il)++;
	}
}

char	*next_word(const char *line, char str[], size_t *il)
{
	size_t	i;

	if (line[*il] == '\0')
		return (NULL);
	i = 0;
	memset(str, 0, ARG_MAX);
	while (isspace(line[*il]))
		(*il)++;
	if (line[*il] == '>' || line[*il] == '<' || line[*il] == '|')
	{
		str[i++] = line[(*il)++];
		if ((line[*il] == '>' || line[*il] == '<')
			&& line[*il] == line[*il - 1])
			str[i++] = line[(*il)++];
	}
	else
		ft_loop(str, line, il);
	return (str);
}
