/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:33:04 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/21 16:36:29 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_var
{
	char			*str;
	int				i;
	char			**envp;
}					t_var;

typedef struct s_cmd_linked
{
	char				*cmd;
	char				**args;
	char				**redir;
	struct s_cmd_linked	*next;
}					t_cmd_linked;

typedef struct s_take
{
	char			*word;
	int				i;
	bool			on_quote;
	struct s_take	*next;
}					t_take;

typedef struct s_return
{
	char			*str;
	int				i;
	bool			on_quote;
}					t_return;

typedef struct s_str_quotes
{
	int				length;
	char			*result;
	int				index;
	bool			quote_open;
	int				i;
}					t_str_quotes;

typedef struct s_get_env
{
	int				i;
	int				j;
	int				k;
	int				len;
}					t_get_env;

// parsing_utils
char				*ft_getenv(char *name, t_var *var);
int					size_name(char *str);
void				ft_itoa_custom(int num, char *str);
char				*get_redirect_word(char *result, t_var *var, int i);

// parsing_take
char				*get_var_word(t_var *var);
char				*get_str_quotes(t_var *input, char quote_type);

// check_syntax
bool				check_parsing(t_return *ret, int size);

int					count_pipe(t_return *ret);
t_return			take_word(t_var *var);
t_cmd_linked		*convert_cmd(t_return *ret, int size);

#endif