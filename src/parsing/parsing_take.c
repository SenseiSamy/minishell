/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_take.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:02:25 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/21 01:24:31 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_var_word
{
	char	*result;
	char	*name;
	int		i;
}			t_var_word;

typedef struct s_convert
{
	char	*result;
	char	*var_value;
	t_var	tmp_var;
	int		result_index;
	int		input_index;
}			t_convert;

static char	*get_var_word_name(t_var *var)
{
	t_var_word	var_word;

	var_word = (t_var_word){NULL, NULL, 0};
	while (var->str[var->i] != '\0' && !ft_isalnum(var->str[var->i])
		&& var->str[var->i] != '_')
		var->i++;
	var_word.name = ft_calloc(sizeof(char), size_name(var->str + var->i) + 1);
	var_word.i = 0;
	while (var->str[var->i] != '\0' && (ft_isalnum(var->str[var->i])
			|| var->str[var->i] == '_'))
	{
		var_word.name[var_word.i] = var->str[var->i];
		var_word.i++;
		var->i++;
	}
	var_word.name[var_word.i] = '\0';
	return (var_word.name);
}

char	*get_var_word(t_var *var)
{
	t_var_word	var_word;

	var_word = (t_var_word){NULL, NULL, 0};
	if (var->str[var->i] == '$' && var->str[var->i + 1] == '?')
	{
		var_word.result = ft_calloc(sizeof(char), 11);
		ft_itoa_custom(0, var_word.result);
		var->i += 2;
		return (var_word.result);
	}
	var_word.name = get_var_word_name(var);
	var_word.result = ft_getenv(var_word.name, var);
	free(var_word.name);
	return (var_word.result);
}

char	*convert_var_word(char *input_str, t_var *var)
{
	t_convert	cov;

	cov = (t_convert){ft_calloc(ft_strlen(input_str) + 1, sizeof(char)),
		NULL, (t_var){NULL, 0, NULL}, 0, 0};
	while (input_str[cov.input_index] != '\0')
	{
		if (input_str[cov.input_index] == '$')
		{
			cov.input_index++;
			cov.tmp_var = (t_var){input_str + cov.input_index, 0, var->envp};
			cov.var_value = get_var_word(&cov.tmp_var);
			if (cov.var_value)
			{
				ft_strcpy(cov.result + cov.result_index, cov.var_value);
				cov.result_index += ft_strlen(cov.var_value);
				free(cov.var_value);
			}
			cov.input_index += cov.tmp_var.i;
		}
		else
			cov.result[cov.result_index++] = input_str[cov.input_index++];
	}
	cov.result[cov.result_index] = '\0';
	return (cov.result);
}

char	*norm_return(t_str_quotes str_quotes, t_var *input, char quote_type)
{
	char	*result;

	str_quotes.result[str_quotes.index] = '\0';
	if (quote_type == '"')
		result = convert_var_word(str_quotes.result, input);
	else
		result = str_quotes.result;
	free(str_quotes.result);
	return (result);
}

char	*get_str_quotes(t_var *input, char quote_type)
{
	t_str_quotes	str_quotes;

	str_quotes = (t_str_quotes){ft_strlen(input->str),
		ft_calloc(1, ft_strlen(input->str) + 2), 0, false, 0};
	while (input->i < str_quotes.length)
	{
		if (input->str[input->i] == quote_type)
		{
			str_quotes.quote_open = !str_quotes.quote_open;
			if (str_quotes.quote_open)
				str_quotes.i = input->i + 1;
			else
			{
				ft_strncpy(str_quotes.result + str_quotes.index,
					input->str + str_quotes.i, input->i - str_quotes.i);
				str_quotes.index += input->i - str_quotes.i;
				if (input->i + 1 < str_quotes.length
					&& input->str[input->i + 1] != quote_type)
					break ;
			}
		}
		input->i++;
	}
	return (norm_return(str_quotes, input, quote_type));
}
