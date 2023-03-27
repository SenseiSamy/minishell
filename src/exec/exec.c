/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:50:47 by snaji             #+#    #+#             */
/*   Updated: 2023/03/27 21:52:48 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

static void	open_redirections(t_cmd *cmd)
{
	if (cmd->redirect_in)
		cmd->fd_in = open(cmd->redirect_in, O_RDONLY);
	if (cmd->redirect_out)
	{
		if (cmd->redirect_out_type == 1)
			cmd->fd_out = open(cmd->redirect_out, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRWXU);
		if (cmd->redirect_out_type == 2)
			cmd->fd_out = open(cmd->redirect_out, O_WRONLY | O_APPEND | O_CREAT,
				S_IRWXU);
	}
}

static void	exec_command(t_exec *exec, int i)
{
	if (exec->cmds[i].fd_in == -1)
		process_exit(exec, exec->cmds[i].redirect_in, strerror(errno));
	if (exec->cmds[i].fd_out == -1)
		process_exit(exec, exec->cmds[i].redirect_out, strerror(errno));
	if (dup2(exec->cmds[i].fd_in, 0) == -1)
		process_exit(exec, exec->cmds[i].args[0], strerror(errno));
	if (dup2(exec->cmds[i].fd_out, 1) == -1)
		process_exit(exec, exec->cmds[i].args[0], strerror(errno));
	close_cmd_fds(exec);
	if (exec->cmds[i].cmd)
		execve(exec->cmds[i].cmd, exec->cmds[i].args, exec->env);
	else
		process_exit(exec, exec->cmds[i].args[0], CMD_ERROR);
	process_exit(exec, exec->cmds[i].args[0], strerror(errno));
}

static int	exec_commands(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->n_cmd)
	{
		if (exec->cmds[i].redirect_in || exec->cmds[i].redirect_out)
			open_redirections(&exec->cmds[i]);
		exec->cmds[i].pid = fork();
		if (exec->cmds[i].pid == -1)
			return (EXIT_FAILURE);
		if (exec->cmds[i].pid == 0)
			exec_command(exec, i);
		if (close2(&exec->cmds[i].fd_in) == EXIT_FAILURE ||
			close2(&exec->cmds[i].fd_out) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++i;
	}
	i = 0;
	while (i < exec->n_cmd)
		waitpid(exec->cmds[i++].pid, NULL, 0);
	return (EXIT_SUCCESS);
}

int	exec(char **env, int n_cmd, t_cmd *cmds)
{
	t_exec	exec;

	exec.env = env;
	exec.n_cmd = n_cmd;
	exec.cmds = cmds;
	if (pipe_setup(&exec) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	assign_pipes(&exec);
	if (exec_commands(&exec) == EXIT_FAILURE)
		return (perror("minishell"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
