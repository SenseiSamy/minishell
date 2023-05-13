/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:33:10 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/13 16:18:40 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_var
{
	char	*name;
	char	*value;
	size_t	i;
}			t_var;

bool	is_on_quote(const char *line, size_t end)
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
		i++;
	}
	if (quote)
		return (true);
	return (false);
}

static char	*get_name(const char *line, size_t il)
{
	char	*name;
	size_t	i;

	i = 0;
	name = calloc(1, sizeof(char) * (strlen(line) + 1));
	if (!name)
		return (NULL);
	il++;
	if (line[il] == '?')
		return (free(name), strdup("?"));
	if (!isalpha(line[il]) && line[il] != '_')
		return (free(name), NULL);
	if (isdigit(line[il]))
		return (name);
	while (isalnum(line[il]) || line[il] == '_')
		name[i++] = line[il++];
	return (name);
}

void	convert_variable(const char *line, size_t *il, char *str, size_t *is)
{
	t_var	var;

	var = (t_var){get_name(line, *il), NULL, 0};
	if (!var.name)
		return ;
	var.value = env_get_value(var.name);
	if (var.value)
	{
		while (var.value[var.i])
		{
			if (!is_on_quote(line, *il)
				&& (var.value[var.i] == '>'
					|| var.value[var.i] == '<' || var.value[var.i] == '|'))
			{
				str[(*is)++] = '"';
				str[(*is)++] = var.value[var.i++];
				str[(*is)++] = '"';
			}
			else
				str[(*is)++] = var.value[var.i++];
		}
	}
	*il += strlen(var.name);
	free(var.name);
}
