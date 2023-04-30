/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 04:07:11 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/29 20:06:24 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

typedef struct s_var
{
	size_t	i_cmd;
	size_t	i_args;
	size_t	i_redir;
	size_t	i_str;
}			t_var;

static bool	on_quote(const char *str, size_t i_str)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i] && i < i_str)
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = '\0';
		i++;
	}
	if (quote)
		return (true);
	return (false);
}

static void	alloc_redir(const char *str, char *word, t_cmd *cmd, t_var *var)
{
	char	*result;
	char	*next;
	char	*tmp;

	next = next_word(str, &var->i_str);
	tmp = ft_strjoin(word, " ");
	result = ft_strjoin(tmp, next);
	free(next);
	free(tmp);
	cmd[var->i_cmd].redirect[var->i_redir] = result;
	var->i_redir++;
	var->i_str++;
}

static void	alloc_args(char *word, t_cmd *cmd, t_var *var)
{
	char	*tmp;

	tmp = ft_strdup(word);
	if (!tmp)
		return ;
	cmd[var->i_cmd].args[var->i_args] = strdup(tmp);
	if (var->i_args == 0)
		cmd[var->i_cmd].cmd = strdup(tmp);
	var->i_args++;
	free(tmp);
}

t_cmd	*init_cmd(const char *str)
{
	size_t	i;
	t_cmd	*cmd;

	cmd = calloc(sizeof(t_cmd), (count_pipe(str) + 2));
	if (is_crash(cmd))
		return (NULL);
	i = 0;
	while (i <= count_pipe(str))
	{
		cmd[i].cmd = NULL;
		cmd[i].args = calloc(sizeof(char *), (ft_strlen(str) + 1));
		if (is_crash(cmd[i].args))
			return (NULL);
		cmd[i].redirect = calloc(sizeof(char *), (ft_strlen(str) + 1));
		if (is_crash(cmd[i].redirect))
			return (NULL);
		i++;
	}
	return (cmd);
}

t_cmd	*conv_cmd(const char *str)
{
	t_cmd	*cmd;
	t_var	var;
	char	*word;

	var = (t_var){0, 0, 0, 0};
	cmd = init_cmd(str);
	word = next_word(str, &var.i_str);
	if (!word)
		return (NULL);
	while (word)
	{
		//printf("word = %s\n", word);
		if (!strcmp(word, "|") && !on_quote(str, var.i_str))
			var = (t_var){var.i_cmd + 1, 0, 0, var.i_str};
		else if ((!strcmp(word, "<") || !strcmp(word, ">")
				|| !strcmp(word, ">>") || !strcmp(word, "<<"))
			&& !on_quote(str, var.i_str))
			alloc_redir(str, word, cmd, &var);
		else
			alloc_args(word, cmd, &var);
		if (var.i_str >= ft_strlen(str))
			break ;
		free(word);
		word = next_word(str, &var.i_str);
	}
	free(word);
	return (cmd);
}
