/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:20:26 by snaji             #+#    #+#             */
/*   Updated: 2023/04/29 19:25:40 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	sighdoc(int sig)
{
	(void)sig;
	close(0);
	*interruption_hdoc() = 1;
	write(1, "> ^C\n", 5);
}

int	add_hdoc(t_hdoc **hdocs, t_hdoc *new)
{
	t_hdoc	*ptr;

	if (hdocs == NULL)
		return (EXIT_FAILURE);
	if (*hdocs == NULL)
		*hdocs = new;
	else
	{
		ptr = *hdocs;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (EXIT_SUCCESS);
}

static void	loop_here_doc(t_exec *exec, t_hdoc *hdoc, char *limiter)
{
	char	*line;
	int		exit_status;

	exit_status = 0;
	line = readline("> ");
	while (line && ft_strcmp(line, limiter) != 0)
	{
		ft_putendl_fd(line, hdoc->fd);
		free(line);
		line = readline("> ");
	}
	if (*interruption_hdoc() == 1)
	{
		exit_status = 1;
		*interruption_hdoc() = 0;
	}
	else if (line == NULL)
	{
		ft_putstr_fd("minishell: warning: here-document at line 32 delimited"
			" by end-of-file (wanted `", 2);
		ft_putstr_fd(limiter, 2);
		ft_putendl_fd("`)", 2);
	}
	else
		free(line);
	close_all_fds(exec);
	cleanup(exec->cmds);
	free_exec(exec);
	env_free();
	exit(exit_status);
}

static int	here_doc_fork(t_exec *exec, int n, int i, char *limiter)
{
	t_hdoc	*hdoc;
	int		pid;

	hdoc = ft_calloc(1, sizeof (t_hdoc));
	if (hdoc == NULL)
		return (errno = EMEM, EXIT_FAILURE);
	hdoc->cmd_n = n;
	hdoc->hd_n = i;
	hdoc->next = NULL;
	hdoc->path = create_file_path_hdoc();
	if (hdoc->path == NULL)
		return (free(hdoc), EXIT_FAILURE);
	hdoc->fd = open(hdoc->path, O_RDWR | O_CREAT, S_IRWXU);
	if (hdoc->fd == -1)
		return (free(hdoc->path), free(hdoc), EXIT_FAILURE);
	add_hdoc(&exec->hdocs, hdoc);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, sighdoc);
		loop_here_doc(exec, hdoc, limiter);
	}
	return (pid);
}

int	here_documents(t_exec *exec)
{
	int		n;
	int		i;
	int		pid;
	int		status;

	n = 0;
	while (n < exec->n_cmd)
	{
		i = 0;
		while (exec->cmds[n].redirect[i])
		{
			if (ft_strncmp(exec->cmds[n].redirect[i], "<<", 2) == 0)
			{
				pid = here_doc_fork(exec, n, i, &exec->cmds[n].redirect[i][3]);
				if (pid == EXIT_FAILURE)
					return (EXIT_FAILURE);
				waitpid(pid, &status, 0);
				if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
					return (3);
			}
			++i;
		}
		++n;
	}
	return (EXIT_SUCCESS);
}
