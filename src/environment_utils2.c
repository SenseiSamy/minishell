/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:04:42 by snaji             #+#    #+#             */
/*   Updated: 2023/05/02 20:42:34 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_shlvl_init(void)
{
	char	*key;
	char	*value;

	if (env_get_var("SHLVL") != NULL)
	{
		value = ft_itoa(ft_atoi(env_get_var("SHLVL")->value) + 1);
		if (value == NULL)
			return (EXIT_FAILURE);
		free(env_get_var("SHLVL")->value);
		env_get_var("SHLVL")->value = value;
	}
	else
	{
		key = ft_strdup("SHLVL");
		value = ft_strdup("1");
		if (key == NULL || value == NULL)
			return (errno = EMEM, EXIT_FAILURE);
		if (env_add(key, value) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	env_add_pwd(void)
{
	char	*key;
	char	*value;

	key = ft_strdup("PWD");
	value = getcwd(NULL, 0);
	if (key == NULL || value == NULL || env_add(key, value) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*env_get_value(char *key)
{
	t_env	*var;

	var = env_get_var(key);
	if (var)
		return (var->value);
	return (NULL);
}
