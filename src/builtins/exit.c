/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:18:48 by snaji             #+#    #+#             */
/*   Updated: 2023/05/02 16:29:41 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_exit(t_exec *exec, char **args)
{
	int	status;

	status = 0;
	if (args[1] != NULL && args[2] != NULL)
		return (error_message("exit", "too many arguments", NULL), 1);
	if (args[1] == NULL)
		ft_atoi(env_get_value("?"));
	else
		status = ft_atoi(args[1]);
	write(2, "exit\n", 5);
	cleanup(exec->cmds);
	free_exec(exec);
	env_free();
	exit(status);
}
