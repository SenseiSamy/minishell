/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 03:51:51 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/23 00:32:28 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct t_parse
{
	int				i_ret;
	int				i_redir;
	int				i_args;
	t_cmd_linked	*cur;
	char			*tmp;
}					t_parse;

static bool	is_redir(char *str)
{
	return (str[0] == '<' || str[0] == '>');
}

static void	new_pipe(t_parse *parse)
{
	parse->cur->args[parse->i_args] = NULL;
	parse->cur->redir[parse->i_redir] = NULL;
	parse->cur->next = ft_calloc(sizeof(t_cmd_linked), 1);
	parse->cur = parse->cur->next;
	parse->i_args = 0;
	parse->i_redir = 0;
	parse->cur->args = ft_calloc(sizeof(char *), 2);
	if (!parse->cur->args)
		exit(1);
	parse->cur->redir = ft_calloc(sizeof(char *), 2);
	if (!parse->cur->redir)
		exit(1);
}

static void	new_redir(t_parse *parse, t_return *ret)
{
	parse->cur->redir = ft_realloc(parse->cur->redir, sizeof(char *)
			* (parse->i_redir + 2));
	parse->tmp = ft_calloc(sizeof(char), ft_strlen(ret[parse->i_ret].str)
			+ ft_strlen(ret[parse->i_ret + 1].str) + 2);
	ft_strcpy(parse->tmp, ret[parse->i_ret].str);
	ft_strcat(parse->tmp, " ");
	ft_strcat(parse->tmp, ret[parse->i_ret + 1].str);
	parse->cur->redir[parse->i_redir] = parse->tmp;
	parse->i_redir++;
	parse->i_ret++;
}

void	parse_return(t_return *ret, int size, t_cmd_linked **cmd)
{
	t_parse	parse;

	parse = (t_parse){0, 0, 0, *cmd, NULL};
	parse.cur->args = ft_calloc(sizeof(char *), 2);
	parse.cur->redir = ft_calloc(sizeof(char *), 2);
	while (parse.i_ret < size)
	{
		if (ret[parse.i_ret].str[0] == '|' && !ret[parse.i_ret].on_quote)
			new_pipe(&parse);
		else if (is_redir(ret[parse.i_ret].str) && !ret[parse.i_ret].on_quote)
			new_redir(&parse, ret);
		else
		{
			if (parse.i_args == 0)
				parse.cur->cmd = ft_strdup(ret[parse.i_ret].str);
			parse.cur->args = ft_realloc(parse.cur->args, sizeof(char *)
					* (parse.i_args + 2));
			parse.cur->args[parse.i_args] = ft_strdup(ret[parse.i_ret].str);
			parse.i_args++;
		}
		parse.i_ret++;
	}
	parse.cur->args[parse.i_args] = NULL;
	parse.cur->redir[parse.i_redir] = NULL;
	parse.cur->next = NULL;
}

t_cmd_linked	*convert_cmd(t_return *ret, int size)
{
	t_cmd_linked	*cmd;

	cmd = ft_calloc(sizeof(t_cmd_linked), 1);
	parse_return(ret, size, &cmd);
	return (cmd);
}
