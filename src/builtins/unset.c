/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:46:45 by snaji             #+#    #+#             */
/*   Updated: 2023/04/24 18:12:02 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args)
{
	t_env	*var;
	int		i;

	i = 0;
	while (args[++i])
	{
		if (ft_strcmp(args[i], "?") == 0)
			continue ;
		var = env_get_var(args[i]);
		if (var != NULL)
			env_delone(var->value); 
	}
	return (0);
}
