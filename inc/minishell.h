/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:28:37 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/15 19:16:26 by snaji            ###   ########.fr       */
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
# include "exec.h"

/* ************************************************************************** */

# define ctrlc 130
# define ctrlslash 131

typedef struct s_minishell	t_minishell;

struct s_minishell
{
	t_env	*env;
	char	*line;
	char	**cmd_line;
	t_cmd	**cmd;
	int		nb_cmd;
	int		nb_redir;
	int		status;
	int		exit;
};

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

/* ************************************************************************** */

/* BUILTINS*/

void	env(t_env *env);
int		export(t_env **env, char **args);
void	unset(t_env **env, char **args);

/* ENVIRONMENT */

t_env	*create_env(char **old_env);
int		add_to_env( t_env **env, char *key, char *value);
t_env	*get_value(t_env *env, char *key);
void	remove_var(t_env **env, char *key);
void	free_env(t_env *env);

/* ************************************************************************** */

#endif
