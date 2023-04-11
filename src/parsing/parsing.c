/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:54:47 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/11 22:32:02 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*join_tokens(char *token1, char *token2)
{
	char	*result;

	result = malloc(strlen(token1) + strlen(token2) + 2);
	strcpy(result, token1);
	ft_strcat(result, " ");
	ft_strcat(result, token2);
	return (result);
}

static char	**parse_redirect(char *line)
{
	char	**redirect;
	char	*token;
	char	*tmp;
	int		i;

	redirect = malloc(sizeof(char *) * (strlen(line) / 2 + 1));
	i = 0;
	token = strtok(line, " ");
	while (token)
	{
		if (ft_strcmp(token, REDIRECT_IN) == 0
			|| ft_strcmp(token, REDIRECT_OUT) == 0
			|| ft_strcmp(token, REDIRECT_OUT_APPEND) == 0
			|| ft_strcmp(token, REDIRECT_IN_APPEND) == 0)
		{
			tmp = ft_strdup(token);
			token = strtok(NULL, " ");
			redirect[i++] = join_tokens(tmp, token);
		}
		token = strtok(NULL, " ");
	}
	redirect[i] = NULL;
	return (redirect);
}

// line = une commande split de pipe
t_cmd	complet_cmd(char *line, char **envp)
{
	t_cmd	cmd;
	char	*line_copy;

	line_copy = ft_strdup(line);
	cmd.args = parse_args(line_copy);
	cmd.cmd = find_cmd_path(cmd.args[0], envp);
	if (cmd.cmd)
	{
		free(cmd.args[0]);
		cmd.args[0] = ft_strdup(cmd.cmd);
	}
	strcpy(line_copy, line);
	cmd.redirect = parse_redirect(line_copy);
	free(line_copy);
	return (cmd);
}
