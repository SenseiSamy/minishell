/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:04:34 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/19 03:52:07 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	no_newline_args(char **args)
{
	int	i;

	i = 0;
	while (args[1][i])
		if (args[1][i++] != 'n')
			return (false);
	return (true);
}

void	ft_echo(int argc, char **argv)
{
	bool	no_newline;
	int		start_arg;
	int		i;

	no_newline = false;
	start_arg = 1;
	if (argc > 1 && no_newline_args(argv))
	{
		no_newline = true;
		start_arg = 2;
	}
	i = 0;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
}
