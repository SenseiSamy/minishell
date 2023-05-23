/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:51:00 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/23 23:53:29 by snaji            ###   ########.fr       */
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
	ft_dprintf(2, "\e[38;5;245m");
	ft_dprintf(2, "  • ▌ ▄ ·. ▪   ▐ ▄ ▪  .▄▄ ·  ▄ .▄▄▄▄ .▄▄▌  ▄▄▌  \n");
	ft_dprintf(2, "  ·██ ▐███▪██ •█▌▐███ ▐█ ▀. ██▪▐█▀▄.▀·██•  ██•  \n");
	ft_dprintf(2, "  ▐█ ▌▐▌▐█·▐█·▐█▐▐▌▐█·▄▀▀▀█▄██▀▀█▐▀▀▪▄██ ▪ ██ ▪ \n");
	ft_dprintf(2, "  ██ ██▌▐█▌▐█▌██▐█▌▐█▌▐█▄▪▐███▌▐▀▐█▄▄▌▐█▌ ▄▐█▌ ▄\n");
	ft_dprintf(2, "  ▀▀  █▪▀▀▀▀▀▀▀▀ █▪▀▀▀ ▀▀▀▀ ▀▀▀ · ▀▀▀ .▀▀▀ .▀▀▀ \n");
	ft_dprintf(2, "\e[0");
}

void	cleanup(t_cmd *cmd)
{
	size_t	i_cmd;
	size_t	i;

	i_cmd = 0;
	while (cmd[i_cmd].cmd || cmd[i_cmd].args || cmd[i_cmd].redirect)
	{
		free(cmd[i_cmd].cmd);
		i = -1;
		while (cmd[i_cmd].args[++i])
			free(cmd[i_cmd].args[i]);
		free(cmd[i_cmd].args);
		i = -1;
		while (cmd[i_cmd].redirect[++i])
			free(cmd[i_cmd].redirect[i]);
		free(cmd[i_cmd].redirect);
		i_cmd++;
	}
	free(cmd[i_cmd].cmd);
	free(cmd[i_cmd].args);
	free(cmd[i_cmd].redirect);
	free(cmd);
}

void	error_message(char *str1, char *str2, char *str3)
{
	if (!str3)
		ft_dprintf(2, "minishell: %s: %s\n", str1, str2);
	else
		ft_dprintf(2, "minishell: %s: %s: %s\n", str1, str2, str3);
}
