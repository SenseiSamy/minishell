/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:03:52 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/02 16:16:54 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_name(char *cur, size_t	start)
{
	size_t	i;

	i = 0;
	while (cur[start + i] && (isalnum(cur[start + i]) || cur[start + i] == '_'))
		i++;
	return (ft_substr(cur, start, i));
}

char	*get_var(char *cur, size_t	start)
{
	char	*key;
	char	*value;
	char	*var;

	key = get_name(cur, start);
	if (!key)
		return (NULL);
	value = env_get_value(key);
	if (!value)
		value = "";
	var = ft_strdup(value);
	free(key);
	return (var);
}

/*
Parcour la chaine str et la copie dans current, et remplace les variables (ex: $HOME) par leur valeur (ex: /Users/cfrancie)
*/
char	*var_conv(const char *str)
{
	char	*cur;
	char	*new;
	size_t	i_cur;
	size_t	i_new;
	char	*tmp;

	i_cur = 0;
	i_new = 0;
	cur = ft_strdup(str);
	if (is_crash(cur))
		return (NULL);
	new = ft_calloc(sizeof(char), (ft_strlen(cur) + 1));
	if (is_crash(new))
		return (NULL);
	while (cur[i_cur])
	{
		if (cur[i_cur] == '$' && cur[i_cur + 1] && (isalnum(cur[i_cur + 1]) || cur[i_cur + 1] == '_'))
		{
			tmp = get_var(cur, i_cur + 1);
			if (tmp)
			{
				ft_strlcpy(&new[i_new], tmp, ft_strlen(tmp) + 1);
				i_new += ft_strlen(tmp);
				free(tmp);
			}
			i_cur += ft_strlen(get_name(cur, i_cur + 1)) + 1;
		}
		else
			new[i_new++] = cur[i_cur++];
	}
}
