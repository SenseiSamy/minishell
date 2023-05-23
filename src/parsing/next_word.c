/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:25:10 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/23 18:06:51 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	ft_issep(char c, char quote)
{
	if (!quote && ((c == '|' || c == '<' || c == '>') || ft_isspace(c)))
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
	ft_memset(str, 0, ft_strlen(str) + 1);
	while (ft_isspace(line[*il]))
		(*il)++;
	if (line[*il] == '\0')
		return (NULL);
	if (line[*il] == '>' || line[*il] == '<' || line[*il] == '|')
	{
		str[i++] = line[(*il)++];
		if ((line[*il] == '>' || line[*il] == '<')
			&& line[*il] == line[*il - 1])
			str[i++] = line[(*il)++];
	}
	else
		ft_loop(str, line, il);
	while (ft_isspace(line[*il]))
		(*il)++;
	return (str);
}
