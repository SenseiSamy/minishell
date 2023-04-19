/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 03:51:51 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/19 03:47:26 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_convert
{
	t_cmd	*cmds;
	int		i_ret;
	int		i_cmds;
	int		i_args;
	int		i_redir;
	int		nb_pipes;
}			t_convert;

static bool	is_redir(char *str, bool on_quote)
{
	return (on_quote == false && (strcmp(str, "<") == 0 || strcmp(str,
				"<<") == 0 || strcmp(str, ">") == 0 || strcmp(str, ">>") == 0));
}

static int	count_pipes(t_return *ret)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (ret[i].str != NULL)
	{
		if (ret[i].str[0] == '|' && ret[i].on_quote == false)
			count++;
		i++;
	}
	return (count);
}

static char	*ft_strjoin(char *s1, char *s2)
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

static void	convert_utils(t_return *ret, t_convert cov, char *tmp)
{
	if (ret[cov.i_ret].str[0] == '|')
	{
		cov = (t_convert){.i_args = 0, .i_redir = 0};
		cov.i_cmds++;
		return ;
	}
	if (is_redir(ret[cov.i_ret].str, ret[cov.i_ret].on_quote))
	{
		if (ret[cov.i_ret + 1].str != NULL)
		{
			tmp = ft_strjoin(ret[cov.i_ret].str, ret[cov.i_ret
					+ 1].str);
			cov.cmds[cov.i_cmds].redir[cov.i_redir++] = tmp;
			cov.i_ret++;
		}
		return ;
	}
	if (ret[cov.i_ret].str != NULL)
	{
		if (cov.i_args == 0)
			cov.cmds[cov.i_cmds].cmd = ret[cov.i_ret].str;
		cov.cmds[cov.i_cmds].args[cov.i_args++] = ret[cov.i_ret].str;
	}
}

t_cmd	*convert_cmd(t_return *ret, int size)
{
	t_convert	cov;
	char		*tmp;

	tmp = NULL;
	cov = (t_convert){malloc(sizeof(t_cmd) * (count_pipes(ret) + 2)),
		-1, 0, 0, 0, count_pipes(ret)};
	while (++cov.i_ret < size)
		convert_utils(ret, cov, tmp);
	return (cov.cmds);
}
