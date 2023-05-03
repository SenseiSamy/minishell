/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:31:16 by snaji             #+#    #+#             */
/*   Updated: 2023/05/03 16:23:01 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_one(char *arg)
{
	int		j;
	char	*value;
	char	*key;

	value = ft_strchr(arg, '=');
	if (value == NULL)
		key = ft_strdup(arg);
	else
	{
		j = 0;
		while (arg[j] != '=')
			++j;
		key = ft_strndup(arg, j);
		value = ft_strdup(value + 1);
		if (value == NULL)
			return (EXIT_FAILURE);
	}
	if (key == NULL)
		return (free(value), EXIT_FAILURE);
	if (ft_strcmp(key, "?") == 0)
		return (free(key), free(value), EXIT_SUCCESS);
	if (env_add(key, value) == EXIT_FAILURE)
		return (free(key), free(value), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_export(char **args)
{
	int		i;
	int		exit_status;

	i = 1;
	exit_status = 0;
	while (args[i])
	{
		if (args[i] && ft_isalpha(args[i][0]) == false && args[i][0] != '_')
		{
			error_message("export", args[i], "not a valid identifier");
			exit_status = 1;
		}
		else if (export_one(args[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++i;
	}
	return (exit_status);
}
