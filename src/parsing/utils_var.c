/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:17:08 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/11 01:35:26 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_var
{
	size_t	res;
	size_t	i;
	char	*tmp;
	char	quote;
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

static void	ft_for_var(const char *str, t_var *var)
{
	var->i++;
	var->tmp = get_name(str, var->i);
	if (!var->tmp[0] || ft_isdigit(var->tmp[0]))
	{
		var->res++;
		free(var->tmp);
		return ;
	}
	if (env_get_value(var->tmp))
		var->res += lenvar(env_get_value(var->tmp));
	free(var->tmp);
	while (str[var->i] && (ft_isalnum(str[var->i]) || str[var->i] == '_'))
		var->i++;
}

size_t	calcule_res_size(const char *str)
{
	t_var	var;

	var = (t_var){0, 0, NULL, '\0'};
	while (str[var.i])
	{
		if (!var.quote && (str[var.i] == '\"' || str[var.i] == '\''))
			var.quote = str[var.i];
		else if (var.quote && str[var.i] == var.quote)
			var.quote = '\0';
		if ((!var.quote || var.quote == '"') && str[var.i] == '$')
			ft_for_var(str, &var);
		var.res++;
		var.i++;
	}
	return (var.res);
}
