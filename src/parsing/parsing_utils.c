/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:49:10 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/22 19:15:28 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_getenv(char *name, t_var *var)
{
	t_get_env	get_env;

	get_env = (t_get_env){0, 0, 0, ft_strlen(name)};
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
			return (ft_strndup(var->envp[get_env.i] + get_env.j + 1,
					get_env.k - get_env.j - 1));
		}
		get_env.i++;
	}
	return (NULL);
}

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

int	size_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
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
	tmp = ft_strdup(result);
	free(result);
	return (tmp);
}

	next_token = (*token)->next;
	if (next_token && next_token->type == WORD)
	{
		new_str = malloc(ft_strlen((*token)->str)
				+ ft_strlen(next_token->str) + 2);
		ft_strcpy(new_str, (*token)->str);
		ft_strcat(new_str, " ");
		ft_strcat(new_str, next_token->str);
		redirect_type = (*token)->type;
		redirect_count = 0;
		if ((*current_cmd)->redirect)
			while ((*current_cmd)->redirect[redirect_count])
				redirect_count++;
		(*current_cmd)->redirect = (char **)ft_realloc((*current_cmd)->redirect,
				(redirect_count + 2) * sizeof(char *));
		(*current_cmd)->redirect[redirect_count] = new_str;
		(*current_cmd)->redirect[redirect_count + 1] = NULL;
		to_remove = next_token;
		(*token)->next = next_token->next;
		free(to_remove->str);
		free(to_remove);
	}
}
// TODO: erreur de norm et utiliser libft pour une fois