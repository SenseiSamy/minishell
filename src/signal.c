/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:38:33 by snaji             #+#    #+#             */
/*   Updated: 2023/04/24 21:28:30 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	handle_sigint_prompt(int sig)
{
	(void)sig;
	exit_status_to_env(130);
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

// static void	handle_sig_child_process(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	int fd = open("ON ARRIVE ICI", O_RDONLY | O_CREAT);
// 	dprintf(fd, "ON ARRIVE ICI2\n");
// 	exit_status_to_env(130);
// 	//exit(130);
// }

void	signal_prompt(void)
{
	signal(SIGINT, &handle_sigint_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_exec(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_child_process(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
