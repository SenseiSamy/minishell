/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:02:43 by snaji             #+#    #+#             */
/*   Updated: 2023/04/17 23:10:55 by snaji            ###   ########.fr       */
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
# include "libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */

# define SYS_ERROR "An error occured with a system call"
# define MALLOC_ERROR "A memory allocation failed"
# define CMD_ERROR "command not found"
# define EXEC_CMD "An error occured while executing a command"
# define EMEM 132

/* ************************************************************************** */
/*                          STRUCTURES AND TYPEDEFS                           */

typedef struct s_cmd	t_cmd;
typedef struct s_exec	t_exec;
typedef struct s_env	t_env;

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

struct s_cmd
{
	char	*cmd;
	char	**args;
	char	**redirect;
	int		fd_in;
	int		fd_out;
	pid_t	pid;
};

struct s_exec
{
	t_env	*env;
	int		n_pipes;
	int		**pipes;
	int		n_cmd;
	t_cmd	*cmds;
	int		**hdocs;
};

/* ************************************************************************** */
/*                            FUNCTIONS PROTOTYPES                            */

int		pipe_setup(t_exec *exec);
int		**create_pipes(int n);
void	assign_pipes(t_exec *exec);
void	free_pipes(int n, int **pipes);
void	open_redirections(t_exec *exec, int n);
int		create_hdocs(t_exec *exec);
void	free_hdocs(t_exec *exec);
int		here_docs(t_exec *exec);
void	free_exec(t_exec *exec);
void	process_exit(t_exec *exec, char *command, char *error);
int		close_all_fds(t_exec *exec);
int		close2(int *fd);
void	free_array_of_str(char **arr);
char	**pass_env_to_cmd(t_env *env);
char	*get_path(char *prog_name, t_env *env);
int		is_a_builtin(t_cmd *cmd);
int		builtin(t_exec *exec, int i);
int		exec_one_builtin(t_exec *exec);
void	perror2(char *str);
int		choose_exit_status(char *error);
int		exec(t_env *env, int n_cmd, t_cmd *cmds);

#endif