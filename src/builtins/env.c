/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:06:09 by snaji             #+#    #+#             */
/*   Updated: 2023/04/22 19:36:16 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	env(void)
{
	t_env	*env;

	env = env_get();
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "?") != 0)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
