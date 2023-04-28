/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:51:00 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/28 20:04:04 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_crash(void *str)
{
	if (!str)
		return (errno = EMEM, 1);
	return (0);
}

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

void	cleanup(t_cmd *cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmd[i].cmd && cmd[i].redirect)
	{
		if (cmd[i].cmd != NULL)
		{
			if (cmd[i].args)
			{
				j = 0;
				while (cmd[i].args[j])
					free(cmd[i].args[j++]);
				free(cmd[i].args);
			}
		}
		if (cmd[i].redirect)
		{
			j = 0;
			while (cmd[i].redirect[j])
				free(cmd[i].redirect[j++]);
			free(cmd[i].redirect);
		}
		i++;
	}
	free(cmd);
}
