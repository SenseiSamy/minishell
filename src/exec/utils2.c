/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:12:41 by snaji             #+#    #+#             */
/*   Updated: 2023/04/16 14:55:14 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*concatenate_env_var(t_env *env)
{
	char	*env_var;
	char	*tmp;

	tmp = ft_strjoin(env->key, "=");
	if (tmp == NULL)
		return (errno = EMEM, NULL);
	env_var = ft_strjoin(tmp, env->value);
	if (env_var == NULL)
		return (errno = EMEM, free(tmp), NULL);
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
	new_env = ft_calloc(i + 1, sizeof (char *));
	if (!new_env)
		return (errno = EMEM, NULL);
	i = 0;
	while (env)
	{
		new_env[i] = concatenate_env_var(env);
		if (new_env[i] == NULL)
			return (free_array_of_str(new_env), NULL);
		env = env->next;
		++i;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	perror2(char *str)
{
	if (errno == EMEM)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(MALLOC_ERROR, 2);
		ft_putstr_fd("\n", 2);
	}
	else
		perror(str);
}

int	exit_status_to_env(t_exec *exec, int status)
{
	char	*status_str;

	status_str = ft_itoa(status);
	if (status_str == NULL)
		return (errno = EMEM, EXIT_FAILURE);
	if (env_add(&exec->env, ft_strdup("?"), status_str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
