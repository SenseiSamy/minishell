/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:04:23 by snaji             #+#    #+#             */
/*   Updated: 2023/04/24 22:04:53 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_singleton(t_env *new_env, int get_or_set)
{
	static t_env	*env = NULL;

	if (get_or_set == 1)
		env = new_env;
	return (env);
}

t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof (t_env));
	if (new == NULL)
		return (errno = EMEM, NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	env_add(char *key, char *value)
{
	t_env	*env;
	t_env	*previous;

	env = env_get();
	if (env == NULL)
	{
		env_singleton(env_new(key, value), 1);
		if (env_get() == NULL)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (free(env->value), free(key), env->value = value,
				EXIT_SUCCESS);
		previous = env;
		env = env->next;
	}
	previous->next = env_new(key, value);
	if (previous->next == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_env	*env_get_var(char *key)
{
	t_env	*env;

	env = env_get();
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	env_delone(char *key)
{
	t_env	*to_remove;
	t_env	*env;

	env = env_get();
	to_remove = env_get_var(key);
	if (to_remove == NULL)
		return ;
	while (env->next != to_remove)
		env = env->next;
	env->next = to_remove->next;
	free(to_remove->key);
	free(to_remove->value);
	free(to_remove);
}
