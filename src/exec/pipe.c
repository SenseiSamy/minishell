/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:02:43 by snaji             #+#    #+#             */
/*   Updated: 2023/04/15 19:12:02 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (errno = EMEM, NULL);
	i = 0;
	while (i < n)
	{
		pipes[i] = ft_calloc(2, sizeof (*pipes[i]));
		if (pipes[i] == NULL)
			return (errno = EMEM, free_pipes(n, pipes), NULL);
		if (pipe(pipes[i]) == -1)
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
		if (i == 0)
			exec->cmds[i].fd_in = 0;
		else
			exec->cmds[i].fd_in = exec->pipes[i - 1][0];
		if (i == exec->n_cmd - 1)
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
