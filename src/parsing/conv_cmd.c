/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:53:25 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/18 15:55:00 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_var
{
	size_t		i_cmd;
	size_t		i_arg;
	size_t		i_red;
	size_t		i_lin;
	char		word[ARG_MAX];
}				t_var;

static size_t	count_pipe(const char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '|' && !is_on_quote(line, i))
			count++;
		i++;
	}
	return (count);
}

static t_cmd	*alloc_cmd(const char *line)
{
	t_cmd	*cmd;
	size_t	i;
	size_t	count;

	i = 0;
	count = count_pipe(line);
	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), (count + 2));
	if (!cmd)
		return (NULL);
	while (i < count + 1)
	{
		cmd[i].cmd = NULL;
		cmd[i].args = (char **)ft_calloc(sizeof(char *),
				(ft_strlen(line) + 1));
		cmd[i].redirect = (char **)ft_calloc(sizeof(char *),
				(ft_strlen(line) + 1));
		i++;
	}
	cmd[i].cmd = NULL;
	cmd[i].args = NULL;
	cmd[i].redirect = NULL;
	return (cmd);
}

static void	assign_redirect(const char *line, t_cmd *cmd, t_var *var)
{
	char	*res;
	char	*tmp;
	char	*tmp2;

	res = ft_strdup(var->word);
	tmp = next_word(line, var->word, &var->i_lin);
	tmp2 = ft_strjoin(res, " ");
	free(res);
	res = ft_strjoin(tmp2, tmp);
	free(tmp2);
	cmd[var->i_cmd].redirect[var->i_red] = res;
	var->i_red++;
}

static void	ft_loop(char *new_line, t_cmd *cmd, t_var var)
{
	while (next_word(new_line, var.word, &var.i_lin))
	{
		if (var.word[0] == '|'
			&& !is_on_quote(new_line, var.i_lin - ft_strlen(var.word) - 1))
		{
			cmd[var.i_cmd].args[var.i_arg] = NULL;
			cmd[var.i_cmd].redirect[var.i_red] = NULL;
			var = (t_var){.i_arg = 0, .i_red = 0, .i_cmd = var.i_cmd + 1,
				.i_lin = var.i_lin};
		}
		else if ((var.word[0] == '>' || var.word[0] == '<')
			&& !is_on_quote(new_line, var.i_lin - ft_strlen(var.word) - 1))
			assign_redirect(new_line, cmd, &var);
		else
		{
			if (var.i_arg == 0)
				cmd[var.i_cmd].cmd = ft_strdup(var.word);
			cmd[var.i_cmd].args[var.i_arg++] = ft_strdup(var.word);
		}
	}
}

t_cmd	*convert_cmd(const char *line)
{
	t_cmd	*cmd;
	t_var	var;
	char	*new_line;

	new_line = pre_parsing(line);
	if (!new_line)
		return (NULL);
	if (is_empty(new_line))
		return (free(new_line), NULL);
	cmd = alloc_cmd(new_line);
	var = (t_var){.i_arg = 0, .i_red = 0, .i_cmd = 0, .i_lin = 0};
	ft_loop(new_line, cmd, var);
	return (free(new_line), cmd);
}
