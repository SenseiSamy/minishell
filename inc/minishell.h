/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:28:37 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/11 22:35:52 by cfrancie         ###   ########.fr       */
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
/*
-chemin de l'executable (ex: /usr/bin/python)
-arguments de la commande, comme argv (ex: {"/usr/bin", "-l", "NULL"})
-nom du fichier d'une commande tel que "< Makefile cat", vaut NULL sinon
-nom du fichier d'une commande tel que "cat lol > Makefile" ou "cat lol >> 
Makefile", vaut NULL sinon
-vaut 1 si le redirect out est un >, vaut 2 si c'est un >>, vaut 0 sinon
-vaut 1 si il y a une here_doc (<<), vaut 0 sinon;
*/
typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	**redirect;
	int		fd_in;
	int		fd_out;
	pid_t	pid;
}	t_cmd;

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

typedef struct s_data
{
	t_env	**env_var;
	t_cmd	**cmd;
	char	**envp;
}	t_data;

/* ************************************************************************** */
t_cmd	complet_cmd(char *line, char **envp);

#endif
