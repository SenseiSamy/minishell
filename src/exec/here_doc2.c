/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:45:39 by snaji             #+#    #+#             */
/*   Updated: 2023/04/28 22:57:34 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	*interruption_hdoc()
{
	static int	interrupted = 0;

	return (&interrupted);
}

char	*create_file_path_hdoc()
{
	const char	base_name[] = "/tmp/minishell_tmp_";
	size_t		i;
	char		*name;
	char		*tmp;

	i = 0;
	while (i < SIZE_MAX)
	{
		tmp = ft_itoa(i);
		if (tmp == NULL)
			return (errno = EMEM, NULL);
		name = ft_strjoin(base_name, tmp);
		free(tmp);
		if (name == NULL)
			return (errno = EMEM, NULL);
		if (access(name, F_OK) == -1)
			return (name);
		free(name);
		++i;
	}
	return (errno = EMEM, NULL);
}

char	*get_hdoc_path(t_hdoc *hdoc, int cmd_n, int hdoc_n)
{
	while (hdoc)
	{
		if (hdoc->cmd_n == cmd_n && hdoc->hd_n == hdoc_n)
			return (hdoc->path);
		hdoc = hdoc->next;
	}
	return (NULL);
}

void	free_hdocs(t_exec *exec)
{
	t_hdoc	*hdocs;
	t_hdoc	*tmp;

	hdocs = exec->hdocs;
	tmp = NULL;
	while (hdocs)
	{
		close2(&hdocs->fd);
		free(hdocs->path);
		tmp = hdocs->next;
		free(hdocs);
		hdocs = tmp;
	}
}

void	delete_tmp_files(t_exec *exec)
{
	t_hdoc	*hdocs;

	hdocs = exec->hdocs;
	while (hdocs)
	{
		unlink(hdocs->path);
		hdocs = hdocs->next;
	}
}
