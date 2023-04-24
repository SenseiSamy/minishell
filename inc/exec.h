/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:02:43 by snaji             #+#    #+#             */
/*   Updated: 2023/04/24 19:57:50 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */

# include "minishell.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */

# define SYS_ERROR "An error occured with a system call"
# define CMD_ERROR "command not found"
# define EXEC_CMD "An error occured while executing a command"
# define EMEM 132

/* ************************************************************************** */
/*                          STRUCTURES AND TYPEDEFS                           */

typedef struct s_exec	t_exec;

struct s_exec
{
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
char	**pass_env_to_cmd(void);
char	*get_path(char *prog_name);
int		is_a_builtin(t_cmd *cmd);
int		builtin(t_exec *exec, int i);
int		exec_one_builtin(t_exec *exec);
int		choose_exit_status(char *error);
int		exec(t_cmd *cmds);

void	cleanup(t_cmd *cmd);

#endif