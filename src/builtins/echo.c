/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:04:34 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/07 18:47:33 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	newline_args(int argc, char **args)
{
	int	n;
	int	i;

	n = 1;
	while (n < argc)
	{
		if (args[n][0] != '-')
			return (n);
		i = 1;
		while (args[n][i])
			if (args[n][i++] != 'n')
				return (n);
		++n;
	}
	return (n);
}

int	ft_echo(int argc, char **argv)
{
	int		start_arg;
	bool	no_newline;

	start_arg = 1;
	no_newline = false;
	if (argc > 1)
		start_arg = newline_args(argc, argv);
	if (start_arg > 1)
		no_newline = true;
	while (start_arg < argc)
	{
		ft_dprintf(1, "%s", argv[start_arg]);
		if (start_arg < argc - 1)
			ft_dprintf(1, " ");
		++start_arg;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
