/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_assign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:06:19 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/11 19:13:26 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(char c, t_env *env)
{
	while (env)
	{
		if (env->name == c)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

// if we are in a quote (single or double) we don't want to replace the variable
char	*replace_var(char *str, t_env *env)
{
	bool	in_quote;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strdup(str);
	in_quote = false;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			in_quote = !in_quote;
		if (str[i] == '$' && !in_quote)
		{
			tmp[j] = get_env_value(str[i + 1], env);
			if (tmp[j] == NULL)
				ft_exit(0);
			i++;
		}
		else
			tmp[j] = str[i];
		i++;
		j++;
	}
	return (tmp);
}

char	*post_assign(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strdup(str);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			tmp[j] = g_status;
			i++;
		}
		else
			tmp[j] = str[i];
		i++;
		j++;
	}
	return (tmp);
}