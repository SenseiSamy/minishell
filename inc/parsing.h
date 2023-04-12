/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:33:04 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/12 03:23:36 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum e_token_type
{
	WORD,
	DOLLAR,
	REDI_IN,
	REDI_OUT,
	REDI_OUT_APPEND,
	REDI_IN_APPEND,
	PIPE,
	END
}					t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_var
{
	t_token			*tokens;
	int				i;
	int				start;
	bool			in_quotes;
	char			quote_char;
}					t_var;

char				**parse_args(char *line);
char				*find_cmd_path(char *cmd, char **envp);
bool				check_syntax(const char *line);

// pre_parsing.c
t_token				*create_token(char *str, t_token_type type);
t_token				*add_token(t_token *list, char *str, t_token_type type);
t_token_type		get_token_type(char *str);
char				*copy_substring(char *str, int start, int end);
t_token				*pre_parsing(char *line, char **envp);

// pre_parsing_utils.c
void				handle_dollar(t_var *var, char *line);
void				handle_quotes(t_var *var, char *line);
void				handle_space(t_var *var, char *line);
void				handle_end_of_line(t_var *var, char *line);

// parsing.c
t_cmd				*create_command(char *cmd_str);
t_cmd				*add_command(t_cmd **commands, char *cmd_str);
void				add_arg_to_command(t_cmd *current_cmd, char *arg_str);
t_cmd				*process_tokens(t_token *tokens, char **envp);

// parsing_utils.c
char				*get_env_var_value(char *var_name, char **envp);
void				handle_dollar_token(t_token **token, char **envp);
void				handle_redirect_token(t_token **token, t_cmd **current_cmd);

#endif