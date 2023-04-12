/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:04:23 by snaji             #+#    #+#             */
/*   Updated: 2023/04/12 22:08:13 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*create_env(char **old_env)
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
		if (add_to_env(&env, key, value) == EXIT_FAILURE)
			return (NULL);
		++i;
	}
	return (env);
}

int	add_to_env(t_env **env, char *key, char *value)
{
	t_env	*i;

	if (env == NULL)
		return (EXIT_FAILURE);
	if (*env == NULL)
	{
		*env = ft_calloc(1, sizeof (t_env));
		if (*env == NULL)
			return (EXIT_FAILURE);
		(*env)->key = key;
		(*env)->value = value;
		(*env)->next = NULL;
		return (EXIT_SUCCESS);
	}
	i = *env;
	while (i->next != NULL)
		i = i->next;
	i->next = ft_calloc(1, sizeof (t_env));
	if (i->next == NULL)
		return (EXIT_FAILURE);
	i->next->key = key;
	i->next->value = value;
	i->next->next = NULL;
	return (EXIT_SUCCESS);
}

t_env	*get_value(t_env *env, char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	remove_var(t_env **env, char *key)
{
	t_env	*to_remove;
	t_env	*tmp;
	t_env	*ptr;

	ptr = *env;
	to_remove = get_value(*env, key);
	if (to_remove == NULL)
		return ;
	if (ptr == to_remove)
	{
		tmp = ptr->next;
		free(ptr->key);
		free(ptr->value);
		free(ptr);
		*env = tmp;
	}
	while (ptr->next != to_remove)
		ptr = ptr->next;
	ptr->next = to_remove->next;
	free(to_remove->key);
	free(to_remove->value);
	free(to_remove);
}

void	free_env(t_env *env)
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

