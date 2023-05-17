/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:24:06 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/17 18:09:10 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_var
{
	size_t	is;
	size_t	il;
	char	quote;
}			t_var;

static bool	after_herdocs(const char *line, size_t end)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i] && i < end)
	{
		if (!quote && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		else if (!quote && (line[i] == '<' && line[i + 1] == '<'))
		{
			i += 2;
			while (ft_isspace(line[i]) && i < end)
				i++;
			if (i == end)
				return (true);
		}
		i++;
	}
	return (false);
}

char	*get_name(const char *str, size_t i)
{
	char	*name;
	size_t	j;

	if (str[i] == '?')
		return (ft_strdup("?"));
	name = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!name)
		return (NULL);
	j = 0;
	if (ft_isdigit(str[i]))
		return (name[j++] = str[i++], name);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		name[j++] = str[i++];
	return (name);
}

void	copy_var(char str[], char *value, size_t *is, char g_quote)
{
	char	quote;
	size_t	i;

	i = 0;
	quote = 0;
	while (value[i])
	{
		if (!quote && (value[i] == '"' || value[i] == '\''))
			quote = value[i];
		else if (quote && quote == value[i])
			quote = '\0';
		else if ((!quote && !g_quote)
			&& (value[i] == '>' || value[i] == '<' || value[i] == '|'))
		{
			str[(*is)++] = '"';
			while (value[i] == '>' || value[i] == '<' || value[i] == '|')
				str[(*is)++] = value[i++];
			str[(*is)++] = '"';
		}
		else
			str[(*is)++] = value[i++];
	}
}

static void	convert_variable(const char *line, char str[], t_var *var)
{
	char	*name;
	char	*value;

	var->il++;
	name = get_name(line, var->il);
	if (!name)
		return ;
	if (name[0] == '?')
		value = env_get_value(name);
	else if (name[0] == '\0'
		&& !((line[var->il] == '\'' || line[var->il] == '"')
			&& !is_on_quote(line, var->il))
		&& !(ft_isalnum(line[var->il]) || line[var->il] == '_'))
	{
		str[var->is++] = '$';
		free(name);
		return ;
	}
	else
		value = env_get_value(name);
	if (value)
		copy_var(str, value, &var->is, var->quote);
	var->il += ft_strlen(name);
	free(name);
}

void	pre_parsing(const char *line, char str[])
{
	t_var	var;

	var = (t_var){0, 0, 0};
	ft_memset(str, 0, ARG_MAX);
	while (line[var.il])
	{
		if (!var.quote && (line[var.il] == '\'' || line[var.il] == '"'))
			var.quote = line[var.il];
		else if (var.quote && line[var.il] == var.quote)
			var.quote = 0;
		if (var.quote != '\'' && line[var.il] == '$'
			&& !after_herdocs(line, var.il))
			convert_variable(line, str, &var);
		else
			str[var.is++] = line[var.il++];
	}
}
