/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:56:32 by snaji             #+#    #+#             */
/*   Updated: 2023/05/17 15:55:57 by snaji            ###   ########.fr       */
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

int	builtin(t_exec *exec, int i, int free, struct s_std std)
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
		exit_status = ft_exit(exec, exec->cmds[i].args, std);
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
	int				status;
	struct s_std	std;

	if (open_redirections_one_builtin(exec, 0) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	std.stdin = dup(0);
	std.stdout = dup(1);
	if (dup2(exec->cmds[0].fd_in, 0) == -1)
		return (EXIT_FAILURE);
	if (dup2(exec->cmds[0].fd_out, 1) == -1)
		return (EXIT_FAILURE);
	close_all_fds(exec);
	status = builtin(exec, 0, 0, std);
	if (dup2(std.stdin, 0) == -1)
		return (EXIT_FAILURE);
	if (dup2(std.stdout, 1) == -1)
		return (EXIT_FAILURE);
	return (close(std.stdin), close(std.stdout), exit_status_to_env(status));
}
