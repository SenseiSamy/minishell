/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:51:00 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/04 18:16:37 by cfrancie         ###   ########.fr       */
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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str2, 2);
	if (str3)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str3, 2);
	}
	ft_putchar_fd('\n', 2);
}
