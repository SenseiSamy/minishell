/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 03:51:51 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/18 03:52:53 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_redir(char *str, bool on_quote)
{
	return (on_quote == false && (strcmp(str, "<") == 0 || strcmp(str,
				"<<") == 0 || strcmp(str, ">") == 0 || strcmp(str, ">>") == 0));
}

int	count_pipes(t_return *ret)
{
	int	count;

	count = 0;
	for (int i = 0; ret[i].str != NULL; i++)
	{
		if (strcmp(ret[i].str, "|") == 0)
		{
			count++;
		}
	}
	return (count);
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

typedef struct s_convert
{
	t_cmd	*cmds;
	int		i_ret;
	int		i_cmds;
	int		i_args;
	int		i_redir;
	int		nb_pipes;
}			t_convert;

//t_return est un tableau qui contient un mot, sont index,
	et si il est entre guillemet.
// la fonction doit remplir le tableau de structure t_cmd,
	il ya autant d'index dans t_cmd qu'il ya de pipe dans la variable str de t_return. les variables de chaque t_cmd doivent ressembler à ceci:
// redir: contient les redirections (<, <<, >,
		>>) concaténer avec le mot qui le suit.
// args: tout les mots qui ne suivent pas une redirections et qui ne sont pas des pipe
// cmd: premier index de args si il existe

t_cmd	*convert_cmd(t_return *ret, int size)
{
	t_convert	convert;
	char		*tmp;

	convert.nb_pipes = count_pipes(ret);
	convert.cmds = malloc(sizeof(t_cmd) * (convert.nb_pipes + 2));
	convert.i_ret = -1;
	convert.i_cmds = 0;
	convert.i_args = 0;
	convert.i_redir = 0;
	while (++convert.i_ret < size)
	{
		if (ret[convert.i_ret].str[0] == '|')
		{
			convert.i_args = 0;
			convert.i_redir = 0;
			convert.i_cmds++;
			continue ;
		}
		if (is_redir(ret[convert.i_ret].str, ret[convert.i_ret].on_quote))
		{
			if (ret[convert.i_ret + 1].str != NULL)
			{
				tmp = ft_strjoin(ret[convert.i_ret].str, ret[convert.i_ret
						+ 1].str);
				convert.cmds[convert.i_cmds].redir[convert.i_redir] = tmp;
				convert.i_redir++;
				convert.i_ret++;
			}
			continue ;
		}
		if (ret[convert.i_ret].str != NULL)
		{
			if (convert.i_args == 0)
				convert.cmds[convert.i_cmds].cmd = ret[convert.i_ret].str;
			convert.cmds[convert.i_cmds].args[convert.i_args] = ret[convert.i_ret].str;
			convert.i_args++;
		}
	}
	return (convert.cmds);
}
