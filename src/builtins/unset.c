/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:46:45 by snaji             #+#    #+#             */
/*   Updated: 2023/04/16 14:52:30 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_env **env, char **args)
{
	t_env	*var;
	int		i;

	i = 0;
	while (args[++i])
	{
		if (ft_strcmp(args[i], "_") == 0)
			continue ;
		var = env_get(*env, args[i]);
		if (var != NULL)
			env_delone(env, var->value);
	}
	return (0);
}