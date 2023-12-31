/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:06:09 by snaji             #+#    #+#             */
/*   Updated: 2023/04/22 20:05:12 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_env(void)
{
	t_env	*env;

	env = env_get();
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "?") != 0 && env->value != NULL)
			ft_dprintf(1, "%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
