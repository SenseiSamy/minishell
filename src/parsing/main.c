/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:38:20 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/28 17:08:47 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_loop(const char *str, size_t *i, char **word, char quote)
{
	size_t	j;

	j = 0;
	while (str[*i])
	{
		if (str[*i] == quote)
		{
			quote = '\0';
			++(*i);
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
			quote = str[(*i)++];
		else if (quote == '\0' && (isspace(str[*i]) || str[*i] == '>'
				|| str[*i] == '<' || str[*i] == '|'))
			break ;
		else
		{
			if ((!quote || quote == '"') && str[*i] == '$' && (str[*i + 1]
					&& !isspace(str[(*i) + 1])))
				ft_var(str, i, word, &j);
			else
				(*word)[j++] = str[(*i)++];
		}
	}
	(*word)[j] = '\0';
}

char	*next_word(const char *str, size_t *i)
{
	char	*word;
	char	quote;

	quote = '\0';
	while (str[*i] && isspace(str[*i]))
		++(*i);
	if (!str[*i])
		return (NULL);
	word = calloc(sizeof(char), (strlen(str) + 1));
	if (!word)
		return (NULL);
	if (str[*i] == '>' || str[*i] == '<')
		return (take_redir(str, word, i));
	if (str[*i] == '|')
		return (take_pipe(str, word, i));
	ft_loop(str, i, &word, quote);
	if (!word)
		return (NULL);
	if (!word[0])
		return (free(word), NULL);
	return (word);
}

char	**ft_split(const char *str)
{
	char	**array;
	char	*word;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	array = calloc(sizeof(char *), (strlen(str) + 1));
	if (!array)
		return (NULL);
	word = next_word(str, &i);
	while (word)
	{
		array[j++] = word;
		word = next_word(str, &i);
	}
	return (array);
}

void	print_cmd(t_cmd **cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmd[i]->cmd != NULL && cmd[i]->args != NULL && cmd[i]->redir != NULL)
	{
		if (cmd[i]->cmd)
			printf("cmd[%zu]: %s\n", i, cmd[i]->cmd);
		j = -1;
		while (cmd[i]->args[++j])
			if (cmd[i]->args[j])
				printf(" args[%zu]: %s\n", j, cmd[i]->args[j]);
		j = -1;
		while (cmd[i]->redir[++j])
			if (cmd[i]->redir[j])
				printf(" redir[%zu]: %s\n", j, cmd[i]->redir[j]);
		++i;
	}
}

void	free_cmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->args[i])
		free(cmd->args[i++]);
	free(cmd->args);
	i = 0;
	while (cmd->redir[i])
		free(cmd->redir[i++]);
	free(cmd->redir);
	free(cmd->cmd);
	free(cmd);
}

int	main(void)
{
	const char	*str;
	// char		**array;
	t_cmd		*cmd;
	// size_t		i;

	str = "echo $HOME \"Hello World >\" | ls '>>' '|' test";
	//printf("%s\n", str);
	if (syntax_check(str))
		return (1);
	// array = ft_split(str);
	// i = 0;
	// while (array[i])
	//  	printf("%s\n", array[i++]);
	cmd = conv_cmd(str);
	print_cmd(&cmd);
	free_cmd(cmd);
	// i = 0;
	// while (array[i])
	// 	free(array[i++]);
	// free(array);
	return (0);
}
