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

#include "exec.h"

static void	swap(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

static int	export_no_arg2(char **env, int len)
{
	int		i;
	char	**split;

	i = -1;
	while (++i < len)
	{
		if (env[i][0] == '?')
			continue ;
		if (ft_strchr(env[i], '=') == NULL)
			ft_dprintf(1, "export %s\n", env[i]);
		else
		{
			split = ft_split(env[i], '=');
			if (split == NULL)
				return (ft_free_array(env), EXIT_FAILURE);
			ft_dprintf(1, "export %s=\"%s\"\n", split[0],
				ft_strchr(env[i], '=') + 1);
			ft_free_array(split);
		}
	}
	ft_free_array(env);
	return (EXIT_SUCCESS);
}

static int	export_no_arg(void)
{
	char	**env;
	char	**min;
	int		i;
	int		j;
	int		len;

	env = pass_env_to_cmd();
	if (env == NULL)
		return (EXIT_FAILURE);
	len = ft_arraylen(env);
	i = 0;
	while (i < len - 1)
	{
		j = i;
		min = &env[i];
		while (j < len)
		{
			if (ft_strcmp(env[j], *min) < 0)
				min = &env[j];
			++j;
		}
		swap(min, &env[i]);
		++i;
	}
	return (export_no_arg2(env, len));
}

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
	if (args[i] == NULL)
	{
		if (export_no_arg() == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (exit_status);
	}
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
