/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 02:47:38 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/11 23:44:55 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	handle_red_error(const char *line, int start, int end, int *i)
{
	char	unexpected_symbols[NAME_MAX];

	if (line[*i] == '\0')
	{
		write(2,
			"minishell: syntax error near unexpected token `newline'\n", 56);
		return (false);
	}
	else if (line[*i] == '<' || line[*i] == '>')
	{
		while (line[end] == '<' || line[end] == '>')
			end++;
		ft_memcpy(unexpected_symbols, &line[start], end - start);
		unexpected_symbols[end - start] = '\0';
		write(2, "minishell: syntax error near unexpected symbol \"", 47);
		write(2, unexpected_symbols, end - start);
		write(2, "\"\n", 2);
		return (false);
	}
	return (true);
}

static bool	check_redirection(const char *line, int *i)
{
	int	start;
	int	end;

	if (line[*i] == '<' || line[*i] == '>')
	{
		start = *i;
		if (line[*i + 1] == line[*i])
			(*i)++;
		(*i)++;
		while (ft_isspace(line[*i]))
			(*i)++;
		end = *i;
		return (handle_red_error(line, start, end, i));
	}
	return (true);
}

static bool	check_pipe(const char *line, int *i)
{
	if (line[*i] == '|')
	{
		(*i)++;
		while (ft_isspace(line[*i]))
			(*i)++;
		if (line[*i] == '\0')
		{
			write(2, "syntax error: unexpected end of file after pipe\n", 47);
			return (false);
		}
	}
	return (true);
}

bool	check_syntax(const char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		while (ft_isspace(line[i]))
			i++;
		if (!check_redirection(line, &i))
			return (false);
		if (!check_pipe(line, &i))
			return (false);
		if (line[i] != '\0')
			i++;
		i++;
	}
	return (true);
}
