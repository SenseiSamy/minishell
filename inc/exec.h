/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:02:43 by snaji             #+#    #+#             */
/*   Updated: 2023/03/30 00:04:01 by snaji            ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */

# define SYS_ERROR "An error occured with a system call"
# define MALLOC_ERROR "An error occured during a memory allocation"
# define CMD_ERROR "command not found"
# define EXEC_CMD "An error occured while executing a command"

/* ************************************************************************** */
/*                          STRUCTURES AND TYPEDEFS                           */

typedef struct s_hdoc	t_hdoc;
typedef struct s_cmd	t_cmd;
typedef struct s_exec	t_exec;

struct s_hdoc
{
	int		cmd_n;
	char	*limiter;
	int		pipe[2];
};

struct s_cmd
{
	char	*cmd;
	char	**args;
	char	*redirect_in;
	char	*redirect_out;
	int		redirect_out_type;
	char	*here_doc;
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
	int		n_hdoc;
	t_hdoc	*hdocs;
};

/* ************************************************************************** */
/*                            FUNCTIONS PROTOTYPES                            */

int		pipe_setup(t_exec *exec);
int		**create_pipes(int n);
void	assign_pipes(t_exec *exec);
void	free_pipes(int n, int **pipes);
int		create_hdocs(t_exec *exec);
void	assign_hdocs(t_exec *exec);
int		close_hdocs(t_exec *exec);
int		here_doc(t_exec *exec);
void	free_exec(t_exec *exec);
void	process_exit(t_exec *exec, char *command, char *error);
int		close_cmd_fds(t_exec *exec);
int		close2(int *fd);
int		exec(char **env, int n_cmd, t_cmd *cmds);

#endif