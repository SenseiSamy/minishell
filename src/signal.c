/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:38:33 by snaji             #+#    #+#             */
/*   Updated: 2023/04/17 23:21:21 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	handle_sigint(int sig)
{
	(void)sig;
	//mettre valeur $? a 130
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigquit(int sig)
{
	(void)sig;
}

void	signal_prompt(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit);
}

void	signal_exec(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}