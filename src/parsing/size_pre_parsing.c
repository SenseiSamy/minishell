/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_pre_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:28:16 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/24 03:13:48 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_var
{
	size_t	is;
	size_t	il;
	char	quote;
}			t_var;

static size_t	copy_redir_pipe(const char *value, t_var *var)
{
	size_t	i;

	i = 0;
	var->is += 2;
	while (value[i] == '>' || value[i] == '<' || value[i] == '|')
	{
		var->is++;
		i++;
	}
	return (i);
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
			i += copy_redir_pipe(&value[i], var);
		else
		{
			var->is++;
			i++;
		}
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
		var->is++;
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

size_t	size_pre_parsing(const char *line, bool is_heredoc)
{
	t_var	var;

	var = (t_var){0, 0, 0};
	while (line[var.il])
	{
		if (!var.quote && (line[var.il] == '\'' || line[var.il] == '"'))
			var.quote = line[var.il];
		else if (var.quote && line[var.il] == var.quote)
			var.quote = 0;
		if ((var.quote != '\'' || is_heredoc) && line[var.il] == '$'
			&& !after_herdocs(line, var.il))
			convert_variable(line, &var);
		else
			var = (t_var){var.is + 1, var.il + 1, var.quote};
	}
	return (var.is);
}
