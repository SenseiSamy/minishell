/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:51:00 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/10 15:58:25 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	print_cmd(t_cmd *cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmd[i].cmd && cmd[i].redirect)
	{
		if (cmd[i].cmd)
			printf("cmd[%zu]: %s\n", i, cmd[i].cmd);
		j = -1;
		while (cmd[i].args[++j])
			if (cmd[i].args[j])
				printf(" args[%zu]: %s\n", j, cmd[i].args[j]);
		j = -1;
		while (cmd[i].redirect[++j])
			if (cmd[i].redirect[j])
				printf(" redirect[%zu]: %s\n", j, cmd[i].redirect[j]);
		++i;
	}
}*/

int	is_crash(void *str)
{
	if (!str)
		return (errno = EMEM, 1);
	return (0);
}

void	print_mininishell(void)
{
	ft_putstr_fd(" ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓"
		"     ██▓    \n", 2);
	ft_putstr_fd("▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒"
		"    ▓██▒    \n", 2);
	ft_putstr_fd("▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░"
		"    ▒██░    \n", 2);
	ft_putstr_fd("▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░"
		"    ▒██░    \n", 2);
	ft_putstr_fd("▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░███"
		"███▒░██████▒\n", 2);
	ft_putstr_fd("░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░"
		"▓  ░░ ▒░▓  ░\n", 2);
	ft_putstr_fd("░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ "
		"▒  ░░ ░ ▒  ░\n", 2);
	ft_putstr_fd("░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ "
		"░     ░ ░   \n", 2);
	ft_putstr_fd("       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    "
		"░  ░    ░  ░\n", 2);
	ft_putstr_fd("                                                          "
		"            \n", 2);
}

void	cleanup(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i].cmd || cmd[i].redirect || cmd[i].args)
	{
		if (cmd[i].cmd != NULL)
			free(cmd[i].cmd);
		if (cmd[i].redirect != NULL)
			ft_free_array(cmd[i].redirect);
		if (cmd[i].args != NULL)
			ft_free_array(cmd[i].args);
		i++;
	}
	free(cmd[i].cmd);
	free(cmd[i].redirect);
	free(cmd[i].args);
	free(cmd);
}

void	error_message(char *str1, char *str2, char *str3)
{
	if (!str3)
		ft_dprintf(2, "minishell: %s: %s\n", str1, str2);
	else
		ft_dprintf(2, "minishell: %s: %s: %s\n", str1, str2, str3);
}
