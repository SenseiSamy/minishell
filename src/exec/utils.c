/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:20:58 by snaji             #+#    #+#             */
/*   Updated: 2023/03/27 21:52:52 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	process_exit(t_exec *exec, char *command, char *error)
{
	if (error)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(error, 2);
	}
	free_exec(exec);
	if (error)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	free_exec(t_exec *exec)
{
	if (exec->pipes)
		free_pipes(exec->n_pipes, exec->pipes);
	if (exec->cmds)
		if (close_cmd_fds(exec) == EXIT_FAILURE)
			perror("minishell");
}

int	close2(int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) == -1)
			return (EXIT_FAILURE);
		*fd = -2;
	}
	return (EXIT_SUCCESS);
}
