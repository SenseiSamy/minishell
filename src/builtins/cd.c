/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:52:49 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/02 16:53:25 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
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
	return (0);
}

/*
int	main(int argc, char *argv[])
{
	char	*path;
	char cwd[PATH_MAX];

	path = NULL;
	if (argc == 2)
		path = argv[1];
	else if (argc > 2)
	{
		fprintf(stderr, "Usage: %s [<path>]\n", argv[0]);
		return (1);
	}
	if (cd(path) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("Current directory: %s\n", cwd);
		else
		{
			perror("getcwd");
			return (1);
		}
	}
	return (0);
}
*/