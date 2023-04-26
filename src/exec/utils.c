/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:20:58 by snaji             #+#    #+#             */
/*   Updated: 2023/04/26 17:48:10 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	process_exit(t_exec *exec, char *command, char *error)
{
	if (error)
		error_message(command, error);
	free_exec(exec);
	cleanup(exec->cmds);
	env_free();
	if (error)
	{
		if (strcmp(error, CMD_ERROR) == 0)
			exit(127);
		if (command && (command[0] == '/' || command[0] == '.') && errno == 13)
			exit(126);
		else
			exit(1);
	}
	exit(0);
}

void	free_exec(t_exec *exec)
{
	close_all_fds(exec);
	if (exec->pipes)
		free_pipes(exec->n_pipes, exec->pipes);
	if (exec->hdocs)
		free_hdocs(exec);
}

int	close_all_fds(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->n_cmd - 1)
	{
		if (exec->pipes)
		{
			close2(&exec->pipes[i][0]);
			close2(&exec->pipes[i][1]);
		}
		if (exec->hdocs)
		{
			close2(&exec->hdocs[i][0]);
			close2(&exec->hdocs[i][1]);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

int	close2(int *fd)
{
	if (*fd >= 3)
	{
		if (close(*fd) == -1)
			return (EXIT_FAILURE);
		*fd = -2;
	}
	return (EXIT_SUCCESS);
}

void	free_array_of_str(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
