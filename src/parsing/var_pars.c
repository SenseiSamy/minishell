/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:03:52 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/09 01:11:02 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_var
{
	size_t	*i;
	size_t	*j;
}	t_var;

char	*get_name(const char *str, size_t i)
{
	char	*res;
	size_t	j;

	if (str[i] == '?')
		return (ft_strdup("?"));
	res = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (is_crash(res))
		return (NULL);
	j = 0;
	if (ft_isdigit(str[i]))
		return (res[j++] = str[i++], res);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		res[j++] = str[i++];
	return (res);
}

void	copy_value(char **res, char *value, size_t *j, char g_quote)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	while (value[i])
	{
		if (!quote && (value[i] == '"' || value[i] == '\''))
			quote = value[i];
		else if (quote && quote == value[i])
			quote = '\0';
		else if ((!quote && !g_quote) && (value[i] == '>' || value[i] == '<'))
		{
			(*res)[(*j)++] = '"';
			if (value[i] == value[i + 1])
				(*res)[(*j)++] = value[i++];
			(*res)[(*j)++] = value[i++];
			(*res)[(*j)++] = '"';
		}
		else
			(*res)[(*j)++] = value[i++];
	}
}

void	for_var_conv(const char *str, char **res, t_var *var, char quote)
{
	char	*name;
	char	*value;

	(*var->i)++;
	name = get_name(str, *var->i);
	if (is_crash(name))
		return ;
	if (name[0] == '?')
		value = env_get_value("?");
	else if (name[0] == '\0' && (str[*var->i] == ' ' || str[*var->i] == '\0'))
	{
		(*res)[(*var->j)++] = '$';
		free(name);
		return ;
	}
	else
		value = env_get_value(name);
	if (value)
		copy_value(res, value, var->j, quote);
	*var->i += ft_strlen(name);
	free(name);
}

char	*var_conv(const char *str)
{
	char	*res;
	char	quote;
	size_t	i;
	size_t	j;

	res = calloc(calcule_res_size(str) + 1, sizeof(char));
	if (is_crash(res))
		return (NULL);
	i = 0;
	j = 0;
	quote = '\0';
	while (str[i])
	{
		if (!quote && (str[i] == '"' || str[i] == '\''))
			quote = str[i];
		else if (quote && quote == str[i])
			quote = '\0';
		else if ((!quote || quote == '"') && str[i] == '$')
		{
			for_var_conv(str, &res, &(t_var){&i, &j}, quote);
			continue ;
		}
		res[j++] = str[i++];
	}
	return (res);
}
