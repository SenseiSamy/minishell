/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:31:16 by snaji             #+#    #+#             */
/*   Updated: 2023/04/28 20:52:53 by cfrancie         ###   ########.fr       */
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
	printf("key: %s\n", key);
	printf("value: %s\n", value);
	if (key == NULL)
		return (free(value), EXIT_FAILURE);
	if (strcmp(key, "?") == 0)
		return (free(key), free(value), EXIT_SUCCESS);
	if (env_add(key, value) == EXIT_FAILURE)
		return (free(key), free(value), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_export(char **args)
{
	int		i;

	i = 1;
	while (args[i])
	{
		if (export_one(args[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
