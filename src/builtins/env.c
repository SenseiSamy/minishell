/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 03:41:13 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/16 03:43:13 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// j'ai pas trouver d'autre solution que ça faut voir ça @samy
extern char	**environ;

void	ft_env(void)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		ft_putstr_fd(environ[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
