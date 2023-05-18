/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 03:28:18 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/18 15:36:17 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
		return (ft_putendl_fd(cwd, 1), free(cwd), 0);
	ft_dprintf(2, "pwd: error retrieving current directory: getcwd: "
		"cannot access parent directories: %s\n", strerror(errno));
	return (1);
}
