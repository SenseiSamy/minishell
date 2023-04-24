/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:50:47 by snaji             #+#    #+#             */
/*   Updated: 2023/04/23 02:43:42 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	count_cmds(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].args != NULL && cmds[i].cmd != NULL
		&& cmds[i].redirect != NULL)
		++i;
	return (i);
}

static void	exec_command(t_exec *exec, int i)
{
	char	*path;
	char	**env;

	open_redirections(exec, i);
	if (dup2(exec->cmds[i].fd_in, 0) == -1)
		process_exit(exec, exec->cmds[i].args[0], strerror(errno));
	if (dup2(exec->cmds[i].fd_out, 1) == -1)
		process_exit(exec, exec->cmds[i].args[0], strerror(errno));
	close_all_fds(exec);
	if (is_a_builtin(&exec->cmds[i]))
		exit(builtin(exec, i));
	if (exec->cmds[i].cmd)
	{
		path = get_path(exec->cmds[i].cmd);
		if (!path)
			process_exit(exec, exec->cmds[i].args[0], CMD_ERROR);
		env = pass_env_to_cmd();
		if (!env)
			process_exit(exec, exec->cmds[i].args[0], MALLOC_ERROR);
		execve(path, exec->cmds[i].args, env);
		free(path);
		free(env);
		process_exit(exec, exec->cmds[i].args[0], strerror(errno));
	}
	exit(EXIT_SUCCESS);
}

static int	exec_commands(t_exec *exec)
{
	int	i;
	int	status;

	status = 0;
	if (exec->n_cmd == 1 && is_a_builtin(&exec->cmds[0]))
		return (exec_one_builtin(exec));
	i = 0;
	while (i < exec->n_cmd)
	{
		exec->cmds[i].pid = fork();
		if (exec->cmds[i].pid == -1)
			return (EXIT_FAILURE);
		if (exec->cmds[i].pid == 0)
			exec_command(exec, i);
		if (close2(&exec->cmds[i].fd_in) == EXIT_FAILURE
			|| close2(&exec->cmds[i].fd_out) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++i;
	}
	i = 0;
	while (i < exec->n_cmd)
		waitpid(exec->cmds[i++].pid, &status, 0);
	return (exit_status_to_env(status));
}

int	exec(t_cmd *cmds)
{
	t_exec	exec;

	exec.n_cmd = count_cmds(cmds);
	exec.cmds = cmds;
	exec.n_pipes = exec.n_cmd - 1;
	exec.pipes = NULL;
	exec.hdocs = NULL;
	if (pipe_setup(&exec) == EXIT_FAILURE)
		return (perror2("minishell"), EXIT_FAILURE);
	assign_pipes(&exec);
	if (create_hdocs(&exec) == EXIT_FAILURE)
		return (free_exec(&exec), EXIT_FAILURE);
	if (here_docs(&exec) == EXIT_FAILURE)
		return (free_exec(&exec), perror2("minishell"), EXIT_FAILURE);
	if (exec_commands(&exec) == EXIT_FAILURE)
		return (free_exec(&exec), perror2("minishell"), EXIT_FAILURE);
	return (free_exec(&exec), EXIT_SUCCESS);
}
