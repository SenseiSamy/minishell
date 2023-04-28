/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:45:39 by snaji             #+#    #+#             */
/*   Updated: 2023/04/28 16:53:49 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	single_here_doc(t_exec *exec, int cmd_n, char *limiter, int fd)
{
	char	*line;

	line = readline("> ");
	while (line && ft_strncmp(line, limiter, ft_strlen(limiter) + 1) != 0)
	{
		ft_putendl_fd(line, exec->hdocs[cmd_n][1]);
		free(line);
		line = readline("> ");
	}
	if (line == NULL)
	{
		ft_putstr_fd("minishell: warning: here-document at line 32 delimited"
			" by end-of-file (wanted `", 2);
		ft_putstr_fd(limiter, 2);
		ft_putendl_fd("`)", 2);
	}
	else
		free(line);
	close2(&exec->hdocs[cmd_n][1]);
}

static int	fork_here_doc(t_exec *exec, int cmd_n, char *limiter)
{
	int	pid;
	int	status;
	int	fd;

	close2(&exec->hdocs[cmd_n][0]);
	if (pipe(exec->hdocs[cmd_n]) == -1)
		return (EXIT_FAILURE);
	fd = exec->hdocs[cmd_n][1];
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		cleanup(exec->cmds);
		free_exec(exec);
		env_free();
		single_here_doc(exec, cmd_n, fd);
		
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		return (3);
	return (EXIT_SUCCESS);
}

int	here_docs(t_exec *exec)
{
	int	n;
	int	i;
	int	exit;

	n = 0;
	while (n < exec->n_cmd)
	{
		i = 0;
		while (exec->cmds[n].redirect[i])
		{
			if (exec->cmds[n].redirect[i][1] == '<')
			{
				exit = fork_here_doc(exec, n, &exec->cmds[n].redirect[i][3]);
				if (exit == EXIT_FAILURE || exit == 3)
					return (3);
			}
			++i;
		}
		++n;
	}
	return (EXIT_SUCCESS);
}