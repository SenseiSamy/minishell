/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 02:07:33 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/02 16:17:24 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*take_redir(const char *str, char *word, size_t *i)
{
	size_t	j;

	j = 0;
	if (str[*i] == str[(*i) + 1])
		word[j++] = str[(*i)++];
	word[j] = str[(*i)++];
	return (word);
}

char	*take_pipe(const char *str, char *word, size_t *i)
{
	size_t	j;

	j = 0;
	word[j++] = str[(*i)++];
	return (word);
}

static char	*conv_var(const char *str, size_t *i)
{
	char	*word;
	char	*key;
	size_t	j;

	j = 0;
	++(*i);
	if (str[*i] == '?')
	{
		++(*i);
		return (ft_strdup("0"));
	}
	word = ft_calloc(sizeof(char), (ft_strlen(str) + 2));
	if (!word)
		return (NULL);
	while (str[*i] && (isalnum(str[*i]) || str[*i] == '_'))
		word[j++] = str[(*i)++];
	key = env_get_value(word);
	if (!key)
		key = "";
	free(word);
	word = ft_strdup(key);
	return (word);
}

static char	*ft_strljoin(char const *s1, char const *s2, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	return (str);
}

void	ft_var(const char *str, size_t *i, char **word, size_t *j)
{
	char	*tmp;
	char	*old_word;

	tmp = conv_var(str, i);
	if (!tmp)
		return ;
	if (*tmp)
	{
		old_word = *word;
		*word = ft_strljoin(*word, tmp, ft_strlen(str));
		free(old_word);
	}
	free(tmp);
	if (!*word)
	{
		*word = ft_calloc(1, sizeof(char));
		if (!*word)
			return ;
	}
	*j = ft_strlen(*word);
}
