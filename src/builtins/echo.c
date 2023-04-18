/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:04:34 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/17 21:05:24 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_usage(void)
{
	printf("Usage: ft_echo [-n] [string ...]\n");
}

void	ft_echo(int argc, char **argv)
{
	bool	no_newline;
	int		start_arg;
	int		i;

	no_newline = false;
	start_arg = 1;
	if (argc > 1 && strcmp(argv[1], "-n") == 0)
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
