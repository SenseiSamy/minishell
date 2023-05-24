/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:18:48 by snaji             #+#    #+#             */
/*   Updated: 2023/05/17 17:02:50 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	is_valid_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_strlen(arg) == 0 || (ft_strlen(arg) == 1 && arg[0] == '-'))
		return (false);
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == false && !(i == 0 && arg[i] == '-'))
			return (false);
		++i;
	}
	return (true);
}

int	ft_exit(t_exec *exec, char **args, struct s_std std)
{
	int		status;

	status = 0;
	if (exec->n_cmd == 1)
		write(2, "exit\n", 5);
	if (args[1] == NULL)
		status = ft_atoi(env_get_value("?"));
	else
	{
		status = 2;
		if (is_valid_arg(args[1]) == false)
			error_message("exit", args[1], "numeric arguement required");
		else if (args[1] != NULL && args[2] != NULL)
			return (error_message("exit", "too many arguments", NULL), 1);
		else
			status = ft_atoi(args[1]);
	}
	close(std.stdin);
	close(std.stdout);
	delete_tmp_files(exec);
	free_exec(exec);
	cleanup(exec->cmds);
	env_free();
	exit(status);
}
