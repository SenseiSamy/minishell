/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:56:32 by snaji             #+#    #+#             */
/*   Updated: 2023/04/15 18:47:11 by snaji            ###   ########.fr       */
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
	int	error;

	error = EXIT_SUCCESS;
	if (ft_strcmp(exec->cmds[i].cmd, "env") == 0)
		env(exec->env);
	else if (ft_strcmp(exec->cmds[i].cmd, "export") == 0)
		error = export(&exec->env, exec->cmds[i].args);
	else if (ft_strcmp(exec->cmds[i].cmd, "unset") == 0)
		unset(&exec->env, exec->cmds[i].args);
	return (error);
}

int	exec_one_builtin(t_exec *exec)
{
	open_redirections(exec, 0);
	if (dup2(exec->cmds[0].fd_in, 0) == -1)
		return (EXIT_FAILURE);
	if (dup2(exec->cmds[0].fd_out, 1) == -1)
		return (EXIT_FAILURE);
	close_all_fds(exec);
	return (builtin(exec, 0));
}
