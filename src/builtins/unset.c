/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:46:45 by snaji             #+#    #+#             */
/*   Updated: 2023/04/15 18:59:10 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_env **env, char **args)
{
	t_env	*var;
	int		i;

	i = 0;
	while (args[++i])
	{
		if (ft_strcmp(args[i], "_") == 0)
			continue ;
		var = get_value(*env, args[i]);
		if (var != NULL)
			remove_var(env, var->value);
	}
}