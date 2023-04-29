/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:50:47 by snaji             #+#    #+#             */
/*   Updated: 2023/04/29 19:18:03 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	wait_cmds(t_exec *exec)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < exec->n_cmd)
	{
		waitpid(exec->cmds[i].pid, &status, 0);
		if (WIFEXITED(status))
			if (exit_status_to_env(WEXITSTATUS(status)) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		if (WIFSIGNALED(status))
		{
			if (exit_status_to_env(128 + WTERMSIG(status)) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (WTERMSIG(status) == 3)
				write(1, "Quit (core dumped)", 18);
			write(1, "\n", 1);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

static void	exec_command2(t_exec *exec, int i, char *path)
{
	char	**env;

	env = pass_env_to_cmd();
	if (!env)
	{
		free(path);
		process_exit(exec, exec->cmds[i].args[0], MALLOC_ERROR);
	}
	execve(path, exec->cmds[i].args, env);
	free(path);
	free(env);
	process_exit(exec, exec->cmds[i].args[0], strerror(errno));
}

static void	exec_command(t_exec *exec, int i)
{
	char	*path;

	open_redirections(exec, i);
	if (dup2(exec->cmds[i].fd_in, 0) == -1 
		|| dup2(exec->cmds[i].fd_out, 1) == -1)
		process_exit(exec, exec->cmds[i].args[0], strerror(errno));
	close_all_fds(exec);
	if (is_a_builtin(&exec->cmds[i]))
		exit(builtin(exec, i));
	if (exec->cmds[i].cmd == NULL)
		process_exit(exec, NULL, NULL);
	path = get_path(exec->cmds[i].cmd);
	if (!path)
		process_exit(exec, exec->cmds[i].args[0], CMD_ERROR);
	if (access(path, X_OK) == -1)
	{
		free(path);
		process_exit(exec, exec->cmds[i].cmd, strerror(errno));
	}
	exec_command2(exec, i, path);
}

static int	exec_commands(t_exec *exec)
{
	int	i;

	if (exec->n_cmd == 1 && is_a_builtin(&exec->cmds[0]))
		return (exec_one_builtin(exec));
	i = 0;
	while (i < exec->n_cmd)
	{
		exec->cmds[i].pid = fork();
		if (exec->cmds[i].pid == -1)
			return (EXIT_FAILURE);
		if (exec->cmds[i].pid == 0)
		{
			signal_child_process();
			exec_command(exec, i);
		}
		if (close2(&exec->cmds[i].fd_in) == EXIT_FAILURE
			|| close2(&exec->cmds[i].fd_out) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++i;
	}
	return (wait_cmds(exec));
}

int	exec(t_cmd *cmds)
{
	t_exec	exec;
	int		exit;

	exec.n_cmd = count_cmds(cmds);
	exec.cmds = cmds;
	exec.n_pipes = exec.n_cmd - 1;
	exec.pipes = NULL;
	exec.hdocs = NULL;
	if (pipe_setup(&exec) == EXIT_FAILURE)
		return (perror2("minishell"), EXIT_FAILURE);
	assign_pipes(&exec);
	exit = here_documents(&exec);
	if (exit == EXIT_FAILURE)
		return (free_exec(&exec), perror2("minishell"), EXIT_FAILURE);
	else if (exit == 3)
		return (free_exec(&exec), EXIT_FAILURE);
	if (exec_commands(&exec) == EXIT_FAILURE)
		return (free_exec(&exec), perror2("minishell"), EXIT_FAILURE);
	return (delete_tmp_files(&exec), free_exec(&exec), EXIT_SUCCESS);
}
