/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:28:37 by cfrancie          #+#    #+#             */
/*   Updated: 2023/03/15 19:32:34 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */

# include "../lib/libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/* ************************************************************************** */

# define ctrlc 130
# define ctrlslash 131

enum	e_token
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND_OUT,
	APPEND_ERR,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
};

int		g_signal;

/* ************************************************************************** */

/* ************************************************************************** */

#endif
