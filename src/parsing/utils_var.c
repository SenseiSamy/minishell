/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:17:08 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/10 18:38:17 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_var
{
	size_t	res;
	size_t	i;
	char	*tmp;
}			t_var;

static size_t	lenvar(char *key)
{
	size_t	i;
	size_t	res;
	char	quote;

	i = 0;
	res = 0;
	quote = '\0';
	while (key[i])
	{
		if (!quote && (key[i] == '"' || key[i] == '\''))
			quote = key[i];
		else if (quote && quote == key[i])
			quote = '\0';
		else if (!quote && (key[i] == '>' || key[i] == '<' || key[i] == '|'))
		{
			if (key[i] == key[i + 1] && key[i] != '|')
				i++;
			res += 4;
		}
		else
			res++;
		i++;
	}
	return (res + 1);
}

size_t	calcule_res_size(const char *str)
{
	t_var	var;

	var = (t_var){0, 0, NULL};
	while (str[var.i])
	{
		if (str[var.i] == '$')
		{
			var.i++;
			var.tmp = get_name(str, var.i);
			if (!var.tmp[0] || ft_isdigit(var.tmp[0]))
			{
				var.res++;
				free(var.tmp);
				continue ;
			}
			if (env_get_value(var.tmp))
				var.res += lenvar(env_get_value(var.tmp));
			free(var.tmp);
			while (str[var.i] && (isalnum(str[var.i]) || str[var.i] == '_'))
				var.i++;
			continue ;
		}
		var = (t_var){var.res + 1, var.i + 1, NULL};
	}
	return (var.res);
}
