/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:18:48 by snaji             #+#    #+#             */
/*   Updated: 2023/04/15 20:07:58 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_exec *exec, char **args)
{
	int	status;

	status = 0;
	if (args[1] == NULL)
		if (get_value(exec->env, "?") != NULL)
			status = ft_atoi(get_value(exec->env, "?")->value);
	else
		status = ft_atoi(args[1]);
	free_exec(exec);
	// il faudra free tout le minishell
	exit(status);
}
