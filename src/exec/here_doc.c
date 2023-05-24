/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:20:26 by snaji             #+#    #+#             */
/*   Updated: 2023/05/24 21:24:32 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

struct s_norminettehihi
{
	int	line_n;
	int	ex;
};

char	*pre_parsing(const char *line, bool is_heredoc);

static void	sighdoc(int sig)
{
	(void)sig;
	close(0);
	*interruption_hdoc() = 1;
	write(2, "> ^C\n", 5);
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

static int	loop_here_doc(t_exec *exec, t_hdoc *hdoc, char *limiter)
{
	char					*line;
	struct s_norminettehihi	z;

	z.ex = 0;
	z.line_n = 0;
	line = readline("> ");
	while (line && ft_strcmp(line, limiter) != 0)
	{
		if (hdoc->expend == 1)
			line = pre_parsing(line, true);
		ft_putendl_fd(line, hdoc->fd);
		free(line);
		line = readline("> ");
		++z.line_n;
	}
	if (*interruption_hdoc() == 1)
		z.ex = 1;
	else if (line == NULL)
		ft_dprintf(2, "minishell: warning: here-document at line %d delimited"
			" by end-of-file (wanted `%s')\n", z.line_n + 1, limiter);
	else
		free(line);
	*interruption_hdoc() = 0;
	close_all_fds(exec);
	return (free_exec(exec), cleanup(exec->cmds), env_free(), exit(z.ex), 0);
}

static int	here_doc_fork(t_exec *exec, int n, int i, char *limiter)
{
	t_hdoc	*hdoc;
	int		pid;

	hdoc = ft_calloc(1, sizeof (t_hdoc));
	if (hdoc == NULL)
		return (errno = EMEM, EXIT_FAILURE);
	*hdoc = (t_hdoc){n, i, 0, 1, create_file_path_hdoc(), NULL};
	if (hdoc->path == NULL)
		return (free(hdoc), EXIT_FAILURE);
	hdoc->fd = open(hdoc->path, O_RDWR | O_CREAT, S_IRWXU);
	if (hdoc->fd == -1)
		return (free(hdoc->path), free(hdoc), EXIT_FAILURE);
	if (ft_strncmp(limiter, "<<< ", 4) == 0)
		hdoc->expend = 0;
	add_hdoc(&exec->hdocs, hdoc);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, sighdoc);
		loop_here_doc(exec, hdoc,
			&limiter[3 + 1 * !hdoc->expend]);
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
				pid = here_doc_fork(exec, n, i, exec->cmds[n].redirect[i]);
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
