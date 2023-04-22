/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:34:35 by snaji             #+#    #+#             */
/*   Updated: 2023/04/22 19:01:21 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(char **old_env)
{
	char	*key;
	char	*value;

	key = ft_strdup("?");
	value = ft_strdup("0");
	if (key == NULL || value == NULL)
		return (errno = EMEM, EXIT_FAILURE);
	if (env_add(key, value) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (old_env && *old_env)
		if (env_copy(old_env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	env_copy(char **old_env)
{
	char	*key;
	char	*value;
	int		j;
	int		i;

	i = 0;
	while (old_env[i])
	{
		j = 0;
		while (old_env[i][j] && old_env[i][j] != '=')
			++j;
		key = ft_strndup(old_env[i], j);
		value = ft_strdup(ft_strchr(old_env[i], '=') + 1);
		if (key == NULL || value == NULL)
			return (errno = EMEM, EXIT_FAILURE);
		if (env_add(key, value) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	exit_status_to_env(int status)
{
	char	*status_str;

	status_str = ft_itoa(status);
	if (status_str == NULL)
		return (errno = EMEM, EXIT_FAILURE);
	if (env_add(ft_strdup("?"), status_str) == EXIT_FAILURE)
		return (errno = EMEM, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	env_free(void)
{
	t_env	*env;
	t_env	*i;

	env = env_get();
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

t_env	*env_get(void)
{
	return (env_singleton(NULL, 0));
}
