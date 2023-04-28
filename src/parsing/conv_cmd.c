/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 04:07:11 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/28 17:08:44 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_var
{
	size_t	i_cmd;
	size_t	i_args;
	size_t	i_redir;
	size_t	i;
}			t_var;

size_t	count_pipe(const char *str)
{
	size_t	i;
	size_t	count;
	char	quote;

	i = 0;
	count = 1;
	quote = '\0';
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = '\0';
		else if (!quote && str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

/*
Regarde si le mot à l'index i est dans des quote ou non et si c'est un >> << > <
*/
int	is_redir(const char *str, char *word, size_t end, bool pipe)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i] && i < end)
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote && quote == str[i])
			quote = '\0';
		i++;
	}
	if ((!pipe && !quote && (!strcmp(word, ">>")
				|| !strcmp(word, "<<") || !strcmp(word, ">")
				|| !strcmp(word, "<")))
		|| (pipe && !quote && !strcmp(word, "|")))
		return (1);
	return (0);
}

void	init_new_index(const char *str, t_cmd *cmd)
{
	cmd->args = calloc(sizeof(char *), (strlen(str) + 1));
	if (!cmd->args)
		return ;
	cmd->redir = calloc(sizeof(char *), (strlen(str) + 1));
	if (!cmd->redir)
		return ;
}

t_cmd	*init_cmds(const char *str)
{
	t_cmd	*cmd;
	size_t	len;
	size_t	j;

	j = 0;
	len = count_pipe(str);
	printf("len = %zu\n", len);
	cmd = calloc(sizeof(t_cmd), (len + 2));
	if (!cmd)
		return (NULL);
	while (j < len + 1)
	{
		init_new_index(str, &cmd[j]);
		j++;
	}
	return (cmd);
}

t_cmd	*conv_cmd(const char *str)
{
	t_cmd	*cmd;
	t_var	var;
	char	*word;

	cmd = init_cmds(str);
	if (!cmd)
		return (NULL);
	var = (t_var){0, 0, 0, 0};
	word = next_word(str, &var.i);
	//printf("word = %s\n", word);
	while (word)
	{
		//printf("word = %s\n", word);
		if (is_redir(str, word, var.i, true))
			var = (t_var){var.i_cmd + 1, 0, 0, var.i};
		if (is_redir(str, word, var.i, false))
			cmd[var.i_cmd].redir[var.i_redir++] = strdup(word);
		else
			cmd[var.i_cmd].args[var.i_args++] = strdup(word);
		free(word);
		word = next_word(str, &var.i);
	}
	free(word);
	return (cmd);
}
