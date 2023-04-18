/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:33:04 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/18 03:52:39 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**redir;
}					t_cmd;

typedef struct s_var
{
	char			*str;
	int				i;
	char			**envp;
}					t_var;

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
} t_return ;

int					count_pipe(t_return (*ret));
t_return			(take_word(t_var *var));
t_cmd				*convert_cmd(t_return (*ret, int size));
int					check_parsing(t_return (*ret, int size));

#endif