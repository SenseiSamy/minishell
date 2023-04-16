/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:04:23 by snaji             #+#    #+#             */
/*   Updated: 2023/04/16 14:42:26 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	env_add(t_env **env, char *key, char *value)
{
	t_env	*i;

	i = env_get(*env, key);
	if (i != NULL)
		env_delone(env, key);
	if (*env == NULL)
	{
		*env = env_new(key, value);
		if (*env == NULL)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	i = *env;
	while (i->next != NULL)
		i = i->next;
	i->next = env_new(key, value);
	if (i->next == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_env	*env_get(t_env *env, char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	env_delone(t_env **env, char *key)
{
	t_env	*to_remove;
	t_env	*tmp;
	t_env	*ptr;

	ptr = *env;
	to_remove = env_get(*env, key);
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
