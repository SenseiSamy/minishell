/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:59:44 by snaji             #+#    #+#             */
/*   Updated: 2023/04/23 01:15:40 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	open_redirect_out(t_exec *exec, int n, int i, char **lfo)
{
	close2(&exec->cmds[n].fd_out);
	if (exec->cmds[n].redirect[i][1] == '>')
	{
		exec->cmds[n].fd_out = open(&exec->cmds[n].redirect[i][3],
				O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		*lfo = &exec->cmds[n].redirect[i][3];
	}
	else
	{
		exec->cmds[n].fd_out = open(&exec->cmds[n].redirect[i][2],
				O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
		*lfo = &exec->cmds[n].redirect[i][2];
	}
}

static void	open_redirect_in(t_exec *exec, int n, int i, char **lfo)
{
	if (exec->cmds[n].fd_in != exec->hdocs[n][0])
		close2(&exec->cmds[n].fd_in);
	if (exec->cmds[n].redirect[i][1] == '<')
		exec->cmds[n].fd_in = exec->hdocs[n][0];
	else
	{
		exec->cmds[n].fd_in = open(&exec->cmds[n].redirect[i][2],
				O_RDONLY);
		*lfo = &exec->cmds[n].redirect[i][2];
	}
}

void	open_redirections(t_exec *exec, int n)
{
	int		i;
	char	*lfo;

	lfo = NULL;
	i = 0;
	while (exec->cmds[n].redirect[i])
	{
		if (exec->cmds[n].redirect[i][0] == '>')
			open_redirect_out(exec, n, i, &lfo);
		else if (exec->cmds[n].redirect[i][0] == '<')
			open_redirect_in(exec, n, i, &lfo);
		if (exec->cmds[n].fd_in == -1 || exec->cmds[n].fd_out == -1)
			process_exit(exec, lfo, strerror(errno));
		++i;
	}
}
