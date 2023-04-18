/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 03:51:28 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/18 03:53:00 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_take_word
{
	char	*result;
	char	*str_quotes;
	int		i;
}			t_take_word;

typedef struct s_var_word
{
	char	*result;
	char	*name;
	int		i;
}			t_var_word;

typedef struct s_str_quotes
{
	int		length;
	char	*result;
	int		index;
	bool	quote_open;
	int		i;
}			t_str_quotes;

void	ft_itoa_custom(int num, char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	if (num == 0)
		str[i++] = '0';
	while (num != 0)
	{
		str[i++] = (num % 10) + '0';
		num /= 10;
	}
	str[i] = '\0';
	j = 0;
	i--;
	while (j < i)
	{
		tmp = str[j];
		str[j] = str[i];
		str[i] = tmp;
		j++;
		i--;
	}
}

char	*get_redirect_word(char *result, t_var *var, int i)
{
	char	*tmp;

	result[i] = var->str[var->i];
	i++;
	var->i++;
	if (var->str[var->i] == var->str[var->i - 1])
	{
		result[i] = var->str[var->i];
		i++;
		var->i++;
	}
	result[i] = '\0';
	tmp = strdup(result);
	free(result);
	return (tmp);
}

char	*get_str_quotes(t_var *input, char quote_type)
{
	t_str_quotes	str_quotes;

	str_quotes = (t_str_quotes){strlen(input->str), calloc(1, strlen(input->str)
			+ 2), 0, false, 0};
	while (input->i < str_quotes.length)
	{
		if (input->str[input->i] == quote_type)
		{
			str_quotes.quote_open = !str_quotes.quote_open;
			if (str_quotes.quote_open)
				str_quotes.i = input->i + 1;
			else
			{
				strncpy(str_quotes.result + str_quotes.index,
						input->str + str_quotes.i,
						input->i - str_quotes.i);
				str_quotes.index += input->i - str_quotes.i;
				if (input->i + 1 < str_quotes.length && input->str[input->i
					+ 1] != quote_type)
					break ;
			}
		}
		input->i++;
	}
	str_quotes.result[str_quotes.index] = '\0';
	return (str_quotes.result);
}

typedef struct s_get_env
{
	int		i;
	int		j;
	int		k;
	int		len;
}			t_get_env;

static char	*ft_getenv(char *name, t_var *var)
{
	t_get_env	get_env;

	get_env = (t_get_env){0, 0, 0, strlen(name)};
	while (var->envp[get_env.i] != NULL)
	{
		get_env.j = 0;
		while (var->envp[get_env.i][get_env.j] == name[get_env.j]
			&& name[get_env.j] != '\0')
			get_env.j++;
		if (get_env.j == get_env.len && var->envp[get_env.i][get_env.j] == '=')
		{
			get_env.k = get_env.j + 1;
			while (var->envp[get_env.i][get_env.k] != '\0')
				get_env.k++;
			return (strndup(var->envp[get_env.i] + get_env.j + 1,
							get_env.k - get_env.j - 1));
		}
		get_env.i++;
	}
	return (NULL);
}

int	size_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && (isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*get_var_word(t_var *var)
{
	t_var_word	var_word;

	var_word = (t_var_word){NULL, NULL, 0};
	if (var->str[var->i] == '$' && var->str[var->i + 1] == '?')
	{
		var_word.result = calloc(sizeof(char), 11);
		ft_itoa_custom(0, var_word.result);
		var->i += 2;
		return (var_word.result);
	}
	while (var->str[var->i] != '\0' && !isalnum(var->str[var->i])
		&& var->str[var->i] != '_')
		var->i++;
	var_word.name = calloc(sizeof(char), size_name(var->str + var->i) + 1);
	var_word.i = 0;
	while (var->str[var->i] != '\0' && (isalnum(var->str[var->i])
			|| var->str[var->i] == '_'))
	{
		var_word.name[var_word.i] = var->str[var->i];
		var_word.i++;
		var->i++;
	}
	var_word.name[var_word.i] = '\0';
	var_word.result = ft_getenv(var_word.name, var);
	free(var_word.name);
	return (var_word.result);
}

void	utilse_quote(t_take_word *take_word, t_var *var)
{
	take_word->str_quotes = get_str_quotes(var, var->str[var->i]);
	strcpy(take_word->result + take_word->i, take_word->str_quotes);
	take_word->i += strlen(take_word->str_quotes);
	free(take_word->str_quotes);
}

t_return	take_word(t_var *var)
{
	t_take_word take_word;
	t_return(ret);
	char *tmp;

	take_word = (t_take_word){calloc(1, strlen(var->str) + 1), NULL, 0};
	ret = (t_return){NULL, var->i, false};
	while (isspace(var->str[var->i]))
		var->i++;
	if (var->str[var->i] == '>' || var->str[var->i] == '<')
	{
		ret.str = get_redirect_word(take_word.result, var, take_word.i);
		return ((t_return){ret.str, var->i, false});
	}
	while (var->str[var->i] != '\0' && !isspace(var->str[var->i]))
	{
		if (var->i > (int)strlen(var->str))
			break ;
		if (var->str[var->i] == '|')
		{
			take_word.result[take_word.i++] = var->str[var->i++];
			break ;
		}
		if (var->str[var->i] == '$')
		{
			tmp = get_var_word(var);
			if (tmp != NULL)
			{
				strcpy(take_word.result + take_word.i, tmp);
				take_word.i += strlen(tmp);
				free(tmp);
			}
		}
		else if (var->str[var->i] == '\'' || var->str[var->i] == '"')
		{
			utilse_quote(&take_word, var);
			ret.on_quote = true;
		}
		else
		{
			if (var->str[var->i] == '>' || var->str[var->i] == '<')
				break ;
			take_word.result[take_word.i++] = var->str[var->i];
		}
		var->i++;
	}
	take_word.result[take_word.i] = '\0';
	ret.i = var->i;
	ret.str = take_word.result;
	return (ret);
}