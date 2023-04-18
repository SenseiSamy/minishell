/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 03:52:06 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/18 03:52:22 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_parsing(t_return *ret, int size)
{
	int i;

	i = -1;
	while (++i < size)
	{
		if (ret[i].on_quote)
			continue ;
		if (strcmp(ret[i].str, "|") == 0)
		{
			if (i + 1 < size && !ret[i + 1].on_quote &&
				(strcmp(ret[i + 1].str, "|") == 0 ||
					strcmp(ret[i + 1].str, ">") == 0 ||
					strcmp(ret[i + 1].str, "<") == 0 ||
					strcmp(ret[i + 1].str, ">>") == 0 ||
					strcmp(ret[i + 1].str, "<<") == 0))
				return (printf("minishell: syntax error near unexpected token '%s'\n",
								ret[i + 1].str),
						-1);
			if (i + 1 == size)
				return (printf("minishell: syntax error near unexpected token 'newline'\n"),
						-1);
		}
		if (strcmp(ret[i].str, ">") == 0 || strcmp(ret[i].str, "<") == 0 ||
			strcmp(ret[i].str, ">>") == 0 || strcmp(ret[i].str, "<<") == 0)
		{
			if (i + 1 < size && !ret[i + 1].on_quote &&
				(strcmp(ret[i + 1].str, "|") == 0 ||
					strcmp(ret[i + 1].str, ">") == 0 ||
					strcmp(ret[i + 1].str, "<") == 0 ||
					strcmp(ret[i + 1].str, ">>") == 0 ||
					strcmp(ret[i + 1].str, "<<") == 0))
				return (printf("minishell: syntax error near unexpected token '%s'\n",
								ret[i + 1].str),
						-1);
			if (i + 1 == size)
				return (printf("minishell: syntax error near unexpected token 'newline'\n"),
						-1);
		}
	}
	return (0);
}