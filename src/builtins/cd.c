/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:52:49 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/10 15:58:38 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	char	*key;
	char	*value;

	key = ft_strdup("OLDPWD");
	value = ft_strdup(env_get_value("PWD"));
	if (key == NULL || value == NULL || env_add(key, value) == EXIT_FAILURE)
		return (perror2("cd"), 1);
	if (args[1] != NULL && args[2] != NULL)
		return (error_message("cd", "too many arguments", NULL), 1);
	if (args[1] == NULL)
	{
		args[1] = env_get_value("HOME");
		if (args[1] == NULL)
			return (error_message("cd", "HOME not set", NULL), 1);
	}
	if (chdir(args[1]) != 0)
		return (error_message("cd", args[1], strerror(errno)), 1);
	if (env_add_pwd() == EXIT_FAILURE)
		return (perror2("pwd"), 1);
	return (0);
}
