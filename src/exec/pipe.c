/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:02:43 by snaji             #+#    #+#             */
/*   Updated: 2023/03/30 00:02:26 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

int	pipe_setup(t_exec *exec)
{
	if (exec->n_pipes == 0)
	{
		exec->pipes = NULL;
		return (EXIT_SUCCESS);
	}
	exec->pipes = create_pipes(exec->n_pipes);
	if (exec->pipes == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	**create_pipes(int n)
{
	int	**pipes;
	int	i;

	pipes = ft_calloc(n, sizeof (*pipes));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < n)
	{
		pipes[i] = ft_calloc(2, sizeof (*pipes[i]));
		if (!pipes[i] || pipe(pipes[i]) == -1)
			return (free_pipes(n, pipes), NULL);
		++i;
	}
	return (pipes);
}

void	assign_pipes(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->n_cmd)
	{
		if (exec->cmds[i].redirect_in || exec->cmds[i].here_doc)
			exec->cmds[i].fd_in = -2;
		else if (i == 0)
			exec->cmds[i].fd_in = 0;
		else
			exec->cmds[i].fd_in = exec->pipes[i - 1][0];
		if (exec->cmds[i].redirect_out)
			exec->cmds[i].fd_out = -2;
		else if (i == exec->n_cmd - 1)
			exec->cmds[i].fd_out = 1;
		else
			exec->cmds[i].fd_out = exec->pipes[i][1];
		++i;
	}
}

void	free_pipes(int n, int **pipes)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pipes[i])
			free(pipes[i]);
		++i;
	}
	free(pipes);
}

int	close_cmd_fds(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->n_cmd - 1)
	{
		if (close2(&exec->cmds[i].fd_in) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (close2(&exec->cmds[i].fd_out) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
