/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:06:09 by snaji             #+#    #+#             */
/*   Updated: 2023/04/22 18:26:46 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env()
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
