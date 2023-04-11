/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:06:09 by snaji             #+#    #+#             */
/*   Updated: 2023/04/11 23:20:41 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*concatenate_env_var(t_env *env)
{
	char	*env_var;
	char	*tmp;

	tmp = ft_strjoin(env->key, "=");
	if (tmp == NULL)
		return (NULL);
	env_var = ft_strjoin(tmp, env->value);
	if (env_var == NULL)
		return (free(tmp), NULL);
	return (free(tmp), env_var);
}

char	**pass_env_to_cmd(t_env *env)
{
	char	**new_env;
	t_env	*ptr;
	int		i;

	i = 0;
	ptr = env;
	while (ptr && ++i)
		ptr = ptr->next;
	new_env = ft_calloc(i, sizeof (char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env)
	{
		new_env[i] = concatenate_env_var(env);
		if (new_env[i] == NULL)
			return (free_array_of_str(new_env), NULL);
		env = env->next;
	}
	return (new_env);
}

void	print_env(t_env *env)
{
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
