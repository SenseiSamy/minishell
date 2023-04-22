/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:20:26 by snaji             #+#    #+#             */
/*   Updated: 2023/04/22 19:40:18 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	single_here_doc(t_exec *exec, int cmd_n, char *limiter)
{
	char	*line;

	close2(&exec->hdocs[cmd_n][0]);
	if (pipe(exec->hdocs[cmd_n]) == -1)
		return (EXIT_FAILURE);
	line = readline("> ");
	while (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) != 0)
	{
		ft_putendl_fd(line, exec->hdocs[cmd_n][1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	close2(&exec->hdocs[cmd_n][1]);
	return (EXIT_SUCCESS);
}

int	here_docs(t_exec *exec)
{
	int	n;
	int	i;

	n = 0;
	while (n < exec->n_cmd)
	{
		i = 0;
		while (exec->cmds[n].redirect[i])
		{
			if (exec->cmds[n].redirect[i][1] == '<')
				if (single_here_doc(exec, n, &exec->cmds[n].redirect[i][3])
					== EXIT_FAILURE)
					return (EXIT_FAILURE);
			++i;
		}
		++n;
	}
	return (EXIT_SUCCESS);
}

int	create_hdocs(t_exec *exec)
{
	int	i;

	exec->hdocs = ft_calloc(exec->n_cmd, sizeof (int *));
	if (exec->hdocs == NULL)
		return (errno = EMEM, EXIT_FAILURE);
	i = 0;
	while (i < exec->n_cmd)
	{
		exec->hdocs[i] = ft_calloc(2, sizeof (int));
		if (exec->hdocs == NULL)
			return (errno = EMEM, free_hdocs(exec), EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

void	free_hdocs(t_exec *exec)
{
	int	i;

	i = 0;
	if (exec->hdocs == NULL)
		return ;
	while (i < exec->n_cmd)
	{
		if (exec->hdocs[i])
		{
			close2(&exec->hdocs[i][0]);
			close2(&exec->hdocs[i][1]);
			free(exec->hdocs[i]);
		}
		++i;
	}
	free(exec->hdocs);
}
