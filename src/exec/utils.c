/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:20:58 by snaji             #+#    #+#             */
/*   Updated: 2023/05/08 18:30:15 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	process_exit(t_exec *exec, char *command, char *error)
{
	int	exit_status;

	exit_status = 0;
	if (error)
	{
		error_message(command, error, NULL);
		if (ft_strcmp(error, CMD_ERROR) == 0)
			exit_status = 127;
		else if (command && (command[0] == '/' || command[0] == '.')
			&& errno == 13)
			exit_status = 126;
		else
			exit_status = 1;
	}
	free_exec(exec);
	cleanup(exec->cmds);
	env_free();
	exit(exit_status);
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
	int		i;
	t_hdoc	*hdoc;

	i = 0;
	while (i < exec->n_cmd)
	{
		close2(&exec->cmds[i].fd_in);
		close2(&exec->cmds[i].fd_out);
		++i;
	}
	hdoc = exec->hdocs;
	while (hdoc)
	{
		close2(&hdoc->fd);
		hdoc = hdoc->next;
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

int	is_a_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}
