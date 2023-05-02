/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:18:48 by snaji             #+#    #+#             */
/*   Updated: 2023/05/02 18:34:55 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	is_valid_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
		if (ft_isdigit(arg[i++]) == false)
			return (false);
	return (true);
}

int	ft_exit(t_exec *exec, char **args)
{
	int		status;
	t_cmd	*cmds;

	status = 0;
	if (args[1] != NULL && args[2] != NULL)
		return (error_message("exit", "too many arguments", NULL), 1);
	if (args[1] == NULL)
		ft_atoi(env_get_value("?"));
	else
	{
		if (is_valid_arg(args[1]) == true)
			status = ft_atoi(args[1]);
		else
		{
			error_message("exit", args[1], "numeric arguement required");
			status = 2;
		}
	}
	write(2, "exit\n", 5);
	cmds = exec->cmds;
	free_exec(exec);
	cleanup(cmds);
	env_free();
	exit(status);
}
