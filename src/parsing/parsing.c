/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:15:08 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/24 03:10:19 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_take_word
{
	char	*result;
	char	*str_quotes;
	int		i;
}			t_take_word;

static void	utilse_quote(t_take_word *take_word, t_var *var)
{
	take_word->str_quotes = get_str_quotes(var, var->str[var->i]);
	ft_strcpy(take_word->result + take_word->i, take_word->str_quotes);
	take_word->i += ft_strlen(take_word->str_quotes);
	free(take_word->str_quotes);
}

static bool	utils_take_word(t_var *var, t_take_word *take_word, t_return *ret)
{
	char	*tmp;

	if (var->str[var->i] == '$')
	{
		tmp = get_var_word(var);
		if (tmp != NULL)
		{
			ft_strcpy(take_word->result + take_word->i, tmp);
			take_word->i += ft_strlen(tmp);
		}
	}
	else if (var->str[var->i] == '\'' || var->str[var->i] == '"')
	{
		utilse_quote(take_word, var);
		ret->on_quote = true;
	}
	else
	{
		if (var->str[var->i] == '>' || var->str[var->i] == '<')
			return (false);
		take_word->result[take_word->i++] = var->str[var->i];
	}
	var->i++;
	return (true);
}

static void	init_take_word(t_take_word *take_word, t_return *ret, t_var *var)
{
	take_word->result = ft_calloc(1, ft_strlen(var->str) + 1);
	take_word->str_quotes = NULL;
	take_word->i = 0;
	ret->str = NULL;
	ret->i = var->i;
	ret->on_quote = false;
}

t_return	take_word(t_var *var)
{
	t_take_word	take_word;
	t_return	ret;

	init_take_word(&take_word, &ret, var);
	while (ft_isspace(var->str[var->i]))
		var->i++;
	if (var->str[var->i] == '>' || var->str[var->i] == '<')
	{
		ret.str = get_redirect_word(take_word.result, var, take_word.i);
		return (ret);
	}
	while (var->i < (int)ft_strlen(var->str) && !ft_isspace(var->str[var->i]))
	{
		if (var->str[var->i] == '|')
		{
			take_word.result[take_word.i++] = var->str[var->i++];
			break ;
		}
		if (utils_take_word(var, &take_word, &ret) == false)
			break ;
	}
	take_word.result[take_word.i] = '\0';
	ret.i = var->i;
	ret.str = take_word.result;
	return (ret);
}
