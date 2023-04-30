/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:38:20 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/29 22:35:43 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_loop(const char *str, size_t *i, char **word, char quote)
{
	size_t	j;

	j = 0;
	while (str[*i])
	{
		if (str[*i] == quote)
		{
			quote = '\0';
			++(*i);
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
			quote = str[(*i)++];
		else if (quote == '\0' && (ft_isspace(str[*i]) || str[*i] == '>'
				|| str[*i] == '<' || str[*i] == '|'))
			break ;
		else
		{
			if ((!quote || quote == '"') && str[*i] == '$' && (str[*i + 1]
					&& !ft_isspace(str[(*i) + 1])))
				ft_var(str, i, word, &j);
			else
				(*word)[j++] = str[(*i)++];
		}
	}
	(*word)[j] = '\0';
}

char	*next_word(const char *str, size_t *i)
{
	char	*word;
	char	quote;

	quote = '\0';
	while (str[*i] && ft_isspace(str[*i]))
		++(*i);
	if (!str[*i])
		return (NULL);
	word = ft_calloc(sizeof(char), (ft_strlen(str) + 1));
	if (!word)
		return (NULL);
	if (str[*i] == '>' || str[*i] == '<')
		return (take_redir(str, word, i));
	if (str[*i] == '|')
		return (take_pipe(str, word, i));
	ft_loop(str, i, &word, quote);
	if (!word)
		return (NULL);
	if (!word[0])
		return (free(word), NULL);
	return (word);
}
