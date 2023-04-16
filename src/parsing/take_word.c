/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 22:02:22 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/16 03:21:02 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <limits.h>

typedef struct s_var_get_quotes
{
	int		length;
	char	*result;
	int		index;
	bool	quote_open;
	int		i;
}			t_var_get_quotes;

typedef struct s_var_take_word
{
	char	result[NAME_MAX];
	char	*quote_string;
	int		i;
}			t_var_take_word;

char	*get_quotes_string(t_var *input, char quote_type)
{
	t_var_get_quotes	var;

	var = (t_var_get_quotes){ft_strlen(input->str),
		malloc(ft_strlen(input->str) + 1), 0, false, 0};
	while (input->i < var.length)
	{
		if (input->str[input->i] == quote_type)
		{
			var.quote_open = !var.quote_open;
			if (var.quote_open)
				var.i = input->i + 1;
			else
			{
				ft_strncpy(var.result + var.index, input->str + var.i,
					input->i - var.i);
				var.index += input->i - var.i;
				if (input->i + 1 < var.length && input->str[input->i
						+ 1] != quote_type)
					break ;
			}
		}
		input->i++;
	}
	var.result[var.index] = '\0';
	return (var.result);
}

char	*get_redir_word(t_var *input, t_var_take_word *var)
{
	var->result[var->i] = input->str[input->i];
	var->i++;
	input->i++;
	if (input->str[input->i] == '>')
	{
		var->result[var->i] = input->str[input->i];
		var->i++;
		input->i++;
	}
	var->result[var->i] = '\0';
	return (ft_strdup(var->result));
}

char	*take_word(t_var *input)
{
	t_var_take_word	var;

	var.i = 0;
	while (ft_isspace(input->str[input->i]))
		input->i++;
	if (input->str[input->i] == '>' || input->str[input->i] == '<')
		return (get_redir_word(input, &var));
	while (input->str[input->i] != '\0' && !ft_isspace(input->str[input->i]))
	{
		if (input->str[input->i] == '\'' || input->str[input->i] == '"')
		{
			var.quote_string = get_quotes_string(input, input->str[input->i]);
			ft_strcpy(var.result + var.i, var.quote_string);
			var.i += ft_strlen(var.quote_string);
			free(var.quote_string);
		}
		else
		{
			var.result[var.i] = input->str[input->i];
			var.i++;
		}
		input->i++;
	}
	var.result[var.i] = '\0';
	return (ft_strdup(var.result));
}
