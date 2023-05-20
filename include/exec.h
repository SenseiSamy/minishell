/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:02:43 by snaji             #+#    #+#             */
/*   Updated: 2023/05/17 15:55:48 by snaji            ###   ########.fr       */
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
typedef struct s_hdoc	t_hdoc;

struct s_std
{
	int	stdin;
	int	stdout;
};

struct s_hdoc
{
	int		cmd_n;
	int		hd_n;
	int		fd;
	char	*path;
	t_hdoc	*next;
};

struct s_exec
{
	int		n_pipes;
	int		**pipes;
	int		n_cmd;
	t_cmd	*cmds;
	t_hdoc	*hdocs;
};

/* ************************************************************************** */
/*                            FUNCTIONS PROTOTYPES                            */

int		pipe_setup(t_exec *exec);
int		**create_pipes(int n);
void	assign_pipes(t_exec *exec);
void	free_pipes(int n, int **pipes);
void	open_redirections(t_exec *exec, int n);
int		open_redirections_one_builtin(t_exec *exec, int n);
char	*create_file_path_hdoc(void);
void	delete_tmp_files(t_exec *exec);
void	free_hdocs(t_exec *exec);
char	*get_hdoc_path(t_hdoc *hdoc, int cmd_n, int hdoc_n);
int		*interruption_hdoc(void);
int		here_documents(t_exec *exec);
void	free_exec(t_exec *exec);
void	process_exit(t_exec *exec, char *command, char *error);
int		close_all_fds(t_exec *exec);
int		close2(int *fd);
int		is_a_directory(char *path);
int		count_cmds(t_cmd *cmds);
char	**pass_env_to_cmd(void);
char	*get_path(char *prog_name);
int		is_a_builtin(t_cmd *cmd);
int		builtin(t_exec *exec, int i, int free, struct s_std std);
int		exec_one_builtin(t_exec *exec);
int		ft_exit(t_exec *exec, char **args, struct s_std std);
int		exec(t_cmd *cmds);

#endif