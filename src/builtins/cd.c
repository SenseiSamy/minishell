/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:52:49 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/02 16:12:23 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(const char *path)
{
	if (path == NULL)
	{
		path = env_get_value("HOME");
		if (path == NULL)
			return (error_message("cd", "HOME not set"), 1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
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