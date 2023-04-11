/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:55:26 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/11 19:05:23 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// take the PATH from envp, without the PATH=, and split the string with ':'
// as a delimiter
static char	**find_path(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

// try to find an executable binary of joined path index of the split_path_sys
// array and cmd_name
static char	*try_path_x_ok(const char *cmd_name, char **split_path_sys)
{
	char	*joined_cmd;
	size_t	i;

	i = 0;
	while (split_path_sys[i])
	{
		joined_cmd = ft_strjoin(split_path_sys[i], cmd_name);
		if (access(joined_cmd, X_OK) == 0)
			return (joined_cmd);
		i++;
	}
	return (NULL);
}

size_t	count_args(char **argc, int *i)
{
	size_t	count;

	count = 0;
	while (argc[*i] && argc[*i][0] != '<' && argc[*i][0] != '>')
	{
		count++;
		(*i)++;
	}
	return (count);
}

t_cmd_args	*find_path(char **envp, char *cmd_name)
{
	t_cmd_args	*cmd;
	char		*path;

	cmd = malloc(sizeof(t_cmd_args));
	cmd->split_path_sys = find_path(envp);
	path = try_path_x_ok(cmd_name, cmd->split_path_sys);
	if (path)
	{
		cmd->path = path;
		cmd->arg = ft_strdup(cmd_name);
	}
	else
	{
		cmd->path = NULL;
		cmd->arg = ft_strdup(cmd_name);
	}
	return (cmd);
}