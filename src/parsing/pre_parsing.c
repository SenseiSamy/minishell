/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:24:06 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/22 17:59:39 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_var
{
	size_t	is;
	size_t	il;
	char	quote;
	char	*new_line;
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

static void	copy_var(char *value, t_var *var)
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
		else if ((!quote && !var->quote)
			&& (value[i] == '>' || value[i] == '<' || value[i] == '|'))
		{
			var->new_line[var->is++] = '"';
			while (value[i] == '>' || value[i] == '<' || value[i] == '|')
				var->new_line[var->is++] = value[i++];
			var->new_line[var->is++] = '"';
		}
		else
			var->new_line[var->is++] = value[i++];
	}
}

static void	convert_variable(const char *line, t_var *var)
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
		var->new_line[var->is++] = '$';
		free(name);
		return ;
	}
	else
		value = env_get_value(name);
	if (value)
		copy_var(value, var);
	var->il += ft_strlen(name);
	free(name);
}

char	*pre_parsing(const char *line)
{
	t_var	var;

	var = (t_var){0, 0, 0, ft_calloc(sizeof(char), size_pre_parsing(line) + 1)};
	if (!var.new_line)
		return (NULL);
	while (line[var.il])
	{
		if (!var.quote && (line[var.il] == '\'' || line[var.il] == '"'))
			var.quote = line[var.il];
		else if (var.quote && line[var.il] == var.quote)
			var.quote = 0;
		if (var.quote != '\'' && line[var.il] == '$' && !after_herdocs(line,
				var.il))
			convert_variable(line, &var);
		else
			var.new_line[var.is++] = line[var.il++];
	}
	return (free((char *)line), var.new_line);
}
