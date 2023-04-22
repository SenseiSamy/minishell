/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:20:58 by snaji             #+#    #+#             */
/*   Updated: 2023/04/22 19:40:25 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		exit(1);
	exit(EXIT_SUCCESS);
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
