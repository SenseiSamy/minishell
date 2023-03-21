/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:51:20 by cfrancie          #+#    #+#             */
/*   Updated: 2023/03/20 18:24:40 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*check_cmd(const char *word)
{
	if (!ft_strcmp(word, "echo"))
		return (ECHO);
	else if (!ft_strcmp(word, "cd"))
		return (CD);
	else if (!ft_strcmp(word, "pwd"))
		return (PWD);
	else if (!ft_strcmp(word, "export"))
		return (EXPORT);
	else if (!ft_strcmp(word, "unset"))
		return (UNSET);
	else if (!ft_strcmp(word, "env"))
		return (ENV);
	else if (!ft_strcmp(word, "exit"))
		return (EXIT);
	else
		return (OTHER);
}

void	*parsing(char *line)
{
	t_cmd	*cmd;
	char	**tab;
	int		i;
	int		j;

	i = 0;
	tab = ft_split(line, ' ');
	if (!tab)
		return (NULL);
	cmd = malloc(sizeof(t_cmd) * (ft_tablen(tab) + 1));
	if (!cmd)
		return (NULL);
	while (tab[i])
	{
	}
}
