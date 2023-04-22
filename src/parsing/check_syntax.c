/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:59:38 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/22 04:09:44 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_redir(char *str)
{
	return (ft_strcmp(str, ">") == 0 || ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0);
}

static bool	is_sep(char *str)
{
	return (ft_strcmp(str, "|") == 0 || is_redir(str));
}

static int	print_error(char *str)
{
	write(2, "minishell: syntax error near unexpected token `", 46);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
	return (1);
}

bool	check_parsing(t_return *ret, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (ret[i].on_quote)
			continue ;
		if (ft_strcmp(ret[i].str, "|") == 0)
		{
			if (i + 1 < size && !ret[i + 1].on_quote && is_sep(ret[i + 1].str))
				return (print_error(ret[i + 1].str));
			if (i + 1 == size)
				return (print_error("newline"));
		}
		if (is_redir(ret[i].str))
		{
			if (i + 1 < size && !ret[i + 1].on_quote && is_sep(ret[i + 1].str))
				return (print_error(ret[i + 1].str));
			if (i + 1 == size)
				return (print_error("newline"));
		}
	}
	return (true);
}
