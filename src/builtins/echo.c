/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:04:34 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/24 18:12:40 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	no_newline_args(char **args)
{
	int	i;

	if (args[1][0] != '-')
		return (false);
	i = 1;
	while (args[1][i])
		if (args[1][i++] != 'n')
			return (false);
	return (true);
}

int	ft_echo(int argc, char **argv)
{
	bool	no_newline;
	int		start_arg;

	no_newline = false;
	start_arg = 1;
	if (argc > 1 && no_newline_args(argv))
	{
		no_newline = true;
		start_arg = 2;
	}
	while (start_arg < argc)
	{
		printf("%s", argv[start_arg]);
		if (start_arg < argc - 1)
			printf(" ");
		start_arg++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
