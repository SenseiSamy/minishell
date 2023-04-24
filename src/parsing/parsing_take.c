/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_take.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:02:25 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/24 03:14:16 by cfrancie         ###   ########.fr       */
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
	t_env		*tmp;

	var_word = (t_var_word){NULL, NULL, 0};
	if (var->str[var->i] == '$' && var->str[var->i + 1] == '?')
	{
		var_word.result = env_get_var("?")->value;
		var->i += 2;
		return (var_word.result);
	}
	var_word.name = get_var_word_name(var);
	tmp = env_get_var(var_word.name);
	if (tmp == NULL)
		return (free(var_word.name), NULL);
	var_word.result = env_get_var(var_word.name)->value;
	free(var_word.name);
	return (var_word.result);
}

char	*convert_var_word(char *input_str, t_var *var)
{
	t_convert	cov;

	cov = (t_convert){ft_calloc(ft_strlen(input_str) + 1, sizeof(char)),
		NULL, (t_var){NULL, 0, NULL}, 0, 0};
	if (is_crash(cov.result))
		return (NULL);
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
			}
			cov.input_index += cov.tmp_var.i;
		}
		else
			cov.result[cov.result_index++] = input_str[cov.input_index++];
	}
	return (cov.result[cov.result_index] = '\0', cov.result);
}

char	*norm_return(t_str_quotes str_quotes, t_var *input, char quote_type)
{
	char	*result;

	str_quotes.result[str_quotes.index] = '\0';
	if (quote_type == '"')
	{
		result = convert_var_word(str_quotes.result, input);
		free(str_quotes.result);
		return (result);
	}
	return (str_quotes.result);
}

char	*get_str_quotes(t_var *input, char quote_type)
{
	t_str_quotes	str_quotes;

	str_quotes = (t_str_quotes){ft_strlen(input->str),
		ft_calloc(1, ft_strlen(input->str) + 2), 0, false, 0};
	if (is_crash(str_quotes.result))
		return (NULL);
	while (input->i < str_quotes.length)
		if (utils_get_str(&str_quotes, input, quote_type))
			break ;
	return (norm_return(str_quotes, input, quote_type));
}
