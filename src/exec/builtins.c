/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:56:32 by snaji             #+#    #+#             */
/*   Updated: 2023/04/16 17:41:39 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "cd") == 0 || ft_strcmp(cmd->cmd, "echo") == 0
		|| ft_strcmp(cmd->cmd, "env") == 0 || ft_strcmp(cmd->cmd, "exit") == 0
		|| ft_strcmp(cmd->cmd, "export") == 0 || ft_strcmp(cmd->cmd, "pwd") == 0
		|| ft_strcmp(cmd->cmd, "unset") == 0)
		return (1);
	return (0);
}

int	builtin(t_exec *exec, int i)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (ft_strcmp(exec->cmds[i].cmd, "env") == 0)
		exit_status = env(exec->env);
	else if (ft_strcmp(exec->cmds[i].cmd, "export") == 0)
		exit_status = export(&exec->env, exec->cmds[i].args);
	else if (ft_strcmp(exec->cmds[i].cmd, "unset") == 0)
		exit_status = unset(&exec->env, exec->cmds[i].args);
	return (exit_status);
}

int	exec_one_builtin(t_exec *exec)
{
	int	status;

	open_redirections(exec, 0);
	if (dup2(exec->cmds[0].fd_in, 0) == -1)
		return (EXIT_FAILURE);
	if (dup2(exec->cmds[0].fd_out, 1) == -1)
		return (EXIT_FAILURE);
	close_all_fds(exec);
	status = builtin(exec, 0);
	return (exit_status_to_env(exec, status));
}
