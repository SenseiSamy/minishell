/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:34:35 by snaji             #+#    #+#             */
/*   Updated: 2023/04/16 14:50:32 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_copy(char **old_env)
{
	t_env	*env;
	char	*key;
	char	*value;
	int		j;
	int		i;

	i = 0;
	env = NULL;
	while (old_env[i])
	{
		j = 0;
		while (old_env[i][j] && old_env[i][j] != '=')
			++j;
		key = ft_strndup(old_env[i], j);
		value = ft_strdup(ft_strchr(old_env[i], '=') + 1);
		if (key == NULL || value == NULL)
			return (NULL);
		if (env_add(&env, key, value) == EXIT_FAILURE)
			return (NULL);
		++i;
	}
	return (env);
}

void	env_free(t_env *env)
{
	t_env	*i;

	if (env == NULL)
		return ;
	while (env != NULL)
	{
		free(env->key);
		free(env->value);
		i = env->next;
		free(env);
		env = i;
	}
}
