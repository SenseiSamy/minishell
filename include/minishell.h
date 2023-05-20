/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:28:37 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/20 01:12:50 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */

# define ARG_MAX 1
# define EMEM 132
# define MALLOC_ERROR "A memory allocation failed"

# include "ft_ctype.h"
# include "ft_libft.h"
# include "ft_stdio.h"
# include "ft_stdlib.h"
# include "ft_string.h"
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
# include <errno.h>

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
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef struct s_data
{
	t_env	**env_var;
	t_cmd	**cmd;
	char	**envp;
}			t_data;

/* ************************************************************************** */

/* BUILTINS*/

int		ft_env(void);
int		ft_export(char **args);
int		ft_unset(char **args);
int		ft_echo(int argc, char **args);
int		ft_cd(char **args);
int		ft_pwd(void);

/* ENVIRONMENT */

t_env	*env_singleton(t_env *new_env, int get_or_set);
t_env	*env_get(void);
int		init_env(char **old_env);
int		env_shlvl_init(void);
int		env_add_pwd(void);
int		env_copy(char **old_env);
int		exit_status_to_env(int status);
t_env	*env_new(char *key, char *value);
int		env_add(char *key, char *value);
t_env	*env_get_var(char *key);
char	*env_get_value(char *key);
void	env_delone(char *key);
void	env_free(void);

/* ************************************************************************** */

void	signal_prompt(void);
void	signal_exec(void);
void	signal_child_process(void);
void	perror2(char *str);

/* ************************************************************************** */

t_cmd	*ft_parsing(const char *str);

void	print_mininishell(void);
int		is_crash(void *str);
void	clean_array(char **array);
void	cleanup(t_cmd *cmd);
void	error_message(char *str1, char *str2, char *str3);

#endif
