/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 03:51:51 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/21 16:36:06 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_redir(char *str)
{
	return (str[0] == '<' || str[0] == '>');
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[i + j] = s2[i];
		i++;
	}
	str[i + j] = '\0';
	return (str);
}

void	parse_return(t_return *ret, int size, t_cmd_linked **cmd)
{
	int				i_ret;
	int				i_redir;
	int				i_args;
	t_cmd_linked	*cur;
	char			*tmp;

	i_ret = 0;
	i_redir = 0;
	i_args = 0;
	cur = *cmd;
	cur->args = calloc(sizeof(char *), 2);
	cur->redir = calloc(sizeof(char *), 2);
	while (i_ret < size)
	{
		if (ret[i_ret].str[0] == '|' && ret[i_ret].on_quote == false)
		{
			cur->args[i_args] = NULL;
			cur->redir[i_redir] = NULL;
			cur->next = calloc(sizeof(t_cmd_linked), 1);
			cur = cur->next;
			i_args = 0;
			i_redir = 0;
			cur->args = calloc(sizeof(char *), 2);
			cur->redir = calloc(sizeof(char *), 2);
		}
		else if (is_redir(ret[i_ret].str) && ret[i_ret].on_quote == false)
		{
			cur->redir = realloc(cur->redir, sizeof(char *)
					* (i_redir + 2));
			tmp = ret[i_ret].str;
			tmp = ft_strjoin(tmp, ret[i_ret + 1].str);
			cur->redir[i_redir] = tmp;
			i_redir++;
			i_ret++;
		}
		else
		{
			if (i_args == 0)
				cur->cmd = strdup(ret[i_ret].str);
			cur->args = realloc(cur->args, sizeof(char *) * (i_args
						+ 2));
			cur->args[i_args] = strdup(ret[i_ret].str);
			i_args++;
		}
		i_ret++;
	}
	cur->args[i_args] = NULL;
	cur->redir[i_redir] = NULL;
	cur->next = NULL;
}

t_cmd_linked	*convert_cmd(t_return *ret, int size)
{
	t_cmd_linked	*cmd;

	cmd = calloc(sizeof(t_cmd_linked), 1);
	parse_return(ret, size, &cmd);
	return (cmd);
}
