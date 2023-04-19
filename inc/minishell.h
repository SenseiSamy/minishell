/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:28:37 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/19 03:48:05 by cfrancie         ###   ########.fr       */
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

# define CTRLC 130
# define CTRLSLASH 131

/* ************************************************************************** */

# define OTHER "other"
# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

# define REDIRECT_IN "<"
# define REDIRECT_OUT ">"
# define REDIRECT_OUT_APPEND ">>"
# define REDIRECT_IN_APPEND "<<"

/* ************************************************************************** */

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	**redirect;
	int		fd_in;
	int		fd_out;
	pid_t	pid;
}			t_cmd;

typedef struct s_env
{
	char	*name;
	char	*value;
}			t_env;

typedef struct s_data
{
	t_env	**env_var;
	t_cmd	**cmd;
	char	**envp;
}			t_data;

/* ************************************************************************** */
t_cmd		complet_cmd(char *line, char **envp);

/* ************************************************************************** */
int			ft_cd(const char *path);
void		ft_env(void);
int			ft_pwd(void);
int			ft_unset(const char *name);
void		ft_exit(int status);
void		ft_echo(int argc, char **argv);

#endif
