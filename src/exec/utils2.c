/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:12:41 by snaji             #+#    #+#             */
/*   Updated: 2023/05/20 01:16:54 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	count_cmds(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].args || cmds[i].cmd || cmds[i].redirect)
		++i;
	return (i);
}

static char	*concatenate_env_var(t_env *env)
{
	char	*env_var;
	char	*tmp;

	if (env->value == NULL)
		return (ft_strdup(env->key));
	tmp = ft_strjoin(env->key, "=");
	if (tmp == NULL)
		return (errno = EMEM, NULL);
	env_var = ft_strjoin(tmp, env->value);
	if (env_var == NULL)
		return (errno = EMEM, free(tmp), NULL);
	return (free(tmp), env_var);
}

char	**pass_env_to_cmd(void)
{
	char	**new_env;
	t_env	*env;
	int		i;

	i = 0;
	env = env_get();
	while (env && ++i)
		env = env->next;
	new_env = ft_calloc(i + 1, sizeof (char *));
	if (!new_env)
		return (errno = EMEM, NULL);
	i = 0;
	env = env_get();
	while (env)
	{
		new_env[i] = concatenate_env_var(env);
		if (new_env[i] == NULL)
			return (ft_free_array((void **)new_env), NULL);
		env = env->next;
		++i;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	perror2(char *str)
{
	if (errno == EMEM)
		ft_dprintf(2, "%s: %s\n", str, MALLOC_ERROR);
	else
		perror(str);
}
