/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:56:32 by snaji             #+#    #+#             */
/*   Updated: 2023/05/17 15:18:08 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_a_builtin(t_cmd *cmd)
{
	if (cmd->cmd == NULL)
		return (0);
	if (ft_strcmp(cmd->cmd, "cd") == 0 || ft_strcmp(cmd->cmd, "echo") == 0
		|| ft_strcmp(cmd->cmd, "env") == 0 || ft_strcmp(cmd->cmd, "exit") == 0
		|| ft_strcmp(cmd->cmd, "export") == 0 || ft_strcmp(cmd->cmd, "pwd") == 0
		|| ft_strcmp(cmd->cmd, "unset") == 0)
		return (1);
	return (0);
}

int	builtin(t_exec *exec, int i, int free)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (ft_strcmp(exec->cmds[i].cmd, "env") == 0)
		exit_status = ft_env();
	else if (ft_strcmp(exec->cmds[i].cmd, "export") == 0)
		exit_status = ft_export(exec->cmds[i].args);
	else if (ft_strcmp(exec->cmds[i].cmd, "unset") == 0)
		exit_status = ft_unset(exec->cmds[i].args);
	else if (ft_strcmp(exec->cmds[i].cmd, "cd") == 0)
		exit_status = ft_cd(exec->cmds[i].args);
	else if (ft_strcmp(exec->cmds[i].cmd, "echo") == 0)
		exit_status = ft_echo(ft_arraylen(exec->cmds[i].args),
				exec->cmds[i].args);
	else if (ft_strcmp(exec->cmds[i].cmd, "pwd") == 0)
		exit_status = ft_pwd();
	else if (ft_strcmp(exec->cmds[i].cmd, "exit") == 0)
		exit_status = ft_exit(exec, exec->cmds[i].args);
	if (free == 1)
	{
		free_exec(exec);
		cleanup(exec->cmds);
		env_free();
	}
	return (exit_status);
}

int	exec_one_builtin(t_exec *exec)
{
	int	status;
	int	stdin_fd;
	int	stdout_fd;

	if (open_redirections_one_builtin(exec, 0) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	stdin_fd = dup(0);
	stdout_fd = dup(1);
	if (dup2(exec->cmds[0].fd_in, 0) == -1)
		return (EXIT_FAILURE);
	if (dup2(exec->cmds[0].fd_out, 1) == -1)
		return (EXIT_FAILURE);
	close_all_fds(exec);
	if (strcmp(exec->cmds[0].cmd, "exit") == 0)
	{
		close(stdin_fd);
		close(stdout_fd);
	}
	status = builtin(exec, 0, 0);
	if (dup2(stdin_fd, 0) == -1)
		return (EXIT_FAILURE);
	if (dup2(stdout_fd, 1) == -1)
		return (EXIT_FAILURE);
	return (close(stdin_fd), close(stdout_fd), exit_status_to_env(status));
}
