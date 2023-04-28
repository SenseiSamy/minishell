/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:51:00 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/25 19:31:59 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_mininishell(void)
{
	printf(" ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓");
	printf("     ██▓    \n");
	printf("▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒");
	printf("    ▓██▒    \n");
	printf("▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░");
	printf("    ▒██░    \n");
	printf("▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░");
	printf("    ▒██░    \n");
	printf("▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░███");
	printf("███▒░██████▒\n");
	printf("░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░");
	printf("▓  ░░ ▒░▓  ░\n");
	printf("░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ");
	printf("▒  ░░ ░ ▒  ░\n");
	printf("░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ");
	printf("░     ░ ░   \n");
	printf("       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ");
	printf("░  ░    ░  ░\n");
	printf("                                                          ");
	printf("            \n");
}

void	clean_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	cleanup(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].cmd)
	{
		if (cmd[i].cmd)
		{
			free(cmd[i].cmd);
			cmd[i].cmd = NULL;
		}
		if (cmd[i].args)
		{
			clean_array(cmd[i].args);
			cmd[i].args = NULL;
		}
		if (cmd[i].redirect)
		{
			clean_array(cmd[i].redirect);
			cmd[i].redirect = NULL;
		}
		i++;
	}
	if (cmd)
	{
		free(cmd);
		cmd = NULL;
	}
}
