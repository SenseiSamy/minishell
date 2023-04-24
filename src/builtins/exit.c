/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:18:48 by snaji             #+#    #+#             */
/*   Updated: 2023/04/24 02:30:51 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_exit(t_exec *exec, char **args)
{
	int	status;

	status = 0;
	if (args[1] == NULL)
	{
		if (env_get_var("?") != NULL)
			status = ft_atoi(env_get_var("?")->value);
	}
	else
		status = ft_atoi(args[1]);
	free_exec(exec);
	// il faudra free tout le minishell
	exit(status);
}
