/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:20:26 by snaji             #+#    #+#             */
/*   Updated: 2023/03/30 00:02:49 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

int	create_hdocs(t_exec *exec)
{
	int	i;
	int	j;

	i = 0;
	while (i < exec->n_cmd)
		if (exec->cmds[i++].here_doc != NULL)
			++exec->n_hdoc;
	exec->hdocs = ft_calloc(exec->n_hdoc, sizeof (t_hdoc));
	if (exec->hdocs == NULL)
		return (EXIT_FAILURE);
	i = 0;
	j = 0;
	while (i < exec->n_cmd)
	{
		if (exec->cmds[i].here_doc != NULL)
		{
			exec->hdocs[j].cmd_n = i;
			exec->hdocs[j].limiter = exec->cmds[i].here_doc;
			if (pipe(exec->hdocs[j].pipe) == -1)
				return (EXIT_FAILURE);
			++j;
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

void	assign_hdocs(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->n_hdoc)
	{
		exec->cmds[exec->hdocs[i].cmd_n].fd_in = exec->hdocs[i].pipe[0];
		++i;
	}
}

int	close_hdocs(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->n_hdoc)
	{
		if (close2(&exec->hdocs[i].pipe[0]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (close2(&exec->hdocs[i].pipe[1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	here_doc(t_exec *exec)
{
	int		i;
	char	*line;
	char	*limiter;

	i = 0;
	while (i < exec->n_hdoc)
	{
		limiter = exec->hdocs[i].limiter;
		line = readline("> ");
		while (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) != 0)
		{
			ft_putendl_fd(line, exec->hdocs[i].pipe[1]);
			free(line);
			line = readline("> ");
		}
		free(line);
		close2(&exec->hdocs[i].pipe[1]);
		++i;
	}
	return (EXIT_SUCCESS);
}
