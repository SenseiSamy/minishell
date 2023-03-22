/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:02:43 by snaji             #+#    #+#             */
/*   Updated: 2023/03/22 19:04:08 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../lib/libft/libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */

# define SYS_ERROR "An error occured with a system call"
# define MALLOC_ERROR "An error occured during a memory allocation"
# define CMD_ERROR "command not found"
# define EXEC_CMD "An error occured while executing a command"

/* ************************************************************************** */
/*                          STRUCTURES AND TYPEDEFS                           */

typedef struct s_cmd	t_cmd;
typedef struct s_exec	t_exec;

struct s_cmd
{
	char	*cmd; // chemin de l'executable (ex: /usr/bin/python)
	char	**args; // arguments de la commande, comme argv (ex: {"/usr/bin", "-l", "NULL"})
	char	*redirect_in; // nom du fichier d'une commande tel que "< Makefile cat", vaut NULL sinon
	char	*redirect_out; // nom du fichier d'une commande tel que "cat lol > Makefile" ou "cat lol >> Makefile", vaut NULL sinon
	int		redirect_out_type; // vaut 1 si le redirect out est un >, vaut 2 si c'est un >>, vaut 0 sinon
	int		here_doc; // vaut 1 si il y a une here_doc (<<), vaut 0 sinon; 
	int		fd_in;
	int		fd_out;
	pid_t	pid;
};

struct s_exec
{
	char	**env;
	int		n_pipes;
	int		**pipes;
	int		n_cmd;
	t_cmd	*cmds;
};

/* ************************************************************************** */
/*                            FUNCTIONS PROTOTYPES                            */

int		pipe_setup(t_exec *exec);
int		**create_pipes(int n);
void	assign_pipes(t_exec *exec);
void	free_pipes(int n, int **pipes);
void	free_exec(t_exec *exec);
void	process_exit(t_exec *exec, char *command, char *error);
int		close2(int *fd);

#endif