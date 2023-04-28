/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:20:26 by snaji             #+#    #+#             */
/*   Updated: 2023/04/28 14:13:22 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	create_hdocs(t_exec *exec)
{
	int	i;

	exec->hdocs = ft_calloc(exec->n_cmd, sizeof (int *));
	if (exec->hdocs == NULL)
		return (errno = EMEM, EXIT_FAILURE);
	i = 0;
	while (i < exec->n_cmd)
	{
		exec->hdocs[i] = ft_calloc(2, sizeof (int));
		if (exec->hdocs == NULL)
			return (errno = EMEM, free_hdocs(exec), EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

void	free_hdocs(t_exec *exec)
{
	int	i;

	i = 0;
	if (exec->hdocs == NULL)
		return ;
	while (i < exec->n_cmd)
	{
		if (exec->hdocs[i])
		{
			close2(&exec->hdocs[i][0]);
			close2(&exec->hdocs[i][1]);
			free(exec->hdocs[i]);
		}
		++i;
	}
	free(exec->hdocs);
}
