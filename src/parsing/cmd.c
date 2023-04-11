/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:32:03 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/11 22:37:09 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	*env_path;
	char	*path;
	char	*tmp;
	char	*full_path;

	env_path = get_env_path(envp);
	if (!env_path)
		return (NULL);
	path = strtok(env_path, ":");
	while (path)
	{
		tmp = ft_strdup(path);
		full_path = ft_realloc(tmp, strlen(tmp) + strlen(cmd) + 2);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		path = strtok(NULL, ":");
	}
	return (NULL);
}

char	**parse_args(char *line)
{
	char	**args;
	char	*token;
	int		i;

	args = malloc(sizeof(char *) * (strlen(line) / 2 + 1));
	i = 0;
	token = ft_strtok(line, " ");
	while (token)
	{
		args[i++] = ft_strdup(token);
		token = strtok(NULL, " ");
		if (ft_strcmp(token, REDIRECT_IN) == 0
			|| ft_strcmp(token, REDIRECT_OUT) == 0
			|| ft_strcmp(token, REDIRECT_OUT_APPEND) == 0
			|| ft_strcmp(token, REDIRECT_IN_APPEND) == 0)
			break ;
	}
	args[i] = NULL;
	return (args);
}
