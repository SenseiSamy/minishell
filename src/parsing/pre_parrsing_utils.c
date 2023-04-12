/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parrsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:59:45 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/12 02:19:39 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

void	handle_dollar(t_var *var, char *line)
{
	if (line[var->i] == '$' && !var->in_quotes)
	{
		if (var->i > var->start)
			var->tokens = add_token(var->tokens, copy_substring(line,
						var->start, var->i - 1),
					get_token_type(copy_substring(line, var->start, var->i
							- 1)));
		var->tokens = add_token(var->tokens, copy_substring(line, var->i,
					var->i), DOLLAR);
		var->start = var->i + 1;
	}
}

void	handle_quotes(t_var *var, char *line)
{
	if (is_quote(line[var->i]) && !var->in_quotes)
	{
		var->in_quotes = true;
		var->quote_char = line[var->i];
		var->start = var->i + 1;
	}
	else if (is_quote(line[var->i]) && var->in_quotes
		&& line[var->i] == var->quote_char)
	{
		var->tokens = add_token(var->tokens, copy_substring(line, var->start,
					var->i - 1), WORD);
		var->in_quotes = false;
		var->start = var->i + 1;
	}
}

void	handle_space(t_var *var, char *line)
{
	if (isspace(line[var->i]) && !var->in_quotes)
	{
		if (var->i > var->start)
			var->tokens = add_token(var->tokens, copy_substring(line,
						var->start, var->i - 1),
					get_token_type(copy_substring(line, var->start, var->i
							- 1)));
		var->start = var->i + 1;
	}
}

void	handle_end_of_line(t_var *var, char *line)
{
	if (line[var->i + 1] == '\0')
		var->tokens = add_token(var->tokens, copy_substring(line, var->start,
					var->i), get_token_type(copy_substring(line, var->start,
						var->i)));
}
