/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:38:14 by snaji             #+#    #+#             */
/*   Updated: 2023/04/29 19:02:29 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*find_path(char *prog_name, char *paths)
{
	size_t	i;
	char	**split_paths;
	char	*path;

	split_paths = ft_split(paths, ':');
	if (!split_paths)
		return (NULL);
	i = 0;
	while (split_paths[i])
	{
		path = ft_strjoin(split_paths[i], prog_name);
		if (!path)
			return (ft_free_split(split_paths), free(prog_name), NULL);
		if (access(path, F_OK) == 0)
			return (ft_free_split(split_paths), free(prog_name), path);
		free(path);
		++i;
	}
	return (ft_free_array(split_paths), free(prog_name), NULL);
}

char	*get_path(char *prog_name)
{
	t_env	*tmp;
	char	*paths;

	if (!prog_name || ft_strlen(prog_name) == 0)
		return (NULL);
	if (prog_name[0] == '/' || (prog_name[0] == '.' && prog_name[1] == '/')
		|| (prog_name[0] == '.' && prog_name[1] == '.' && prog_name[2] == '/'))
	{
		if (access(prog_name, F_OK) == 0)
			return (ft_strdup(prog_name));
		return (NULL);
	}
	tmp = env_get_var("PATH");
	if (!tmp)
		return (NULL);
	paths = tmp->value;
	if (!paths)
		return (NULL);
	prog_name = ft_strjoin("/", prog_name);
	if (!prog_name)
		return (NULL);
	return (find_path(prog_name, paths));
}
