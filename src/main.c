/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:24:32 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/17 23:29:22 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parsing(char *line)
{
	t_cmd	*cmds;

	(void)line;
	cmds = malloc(sizeof (t_cmd) * 3);
	if (cmds == NULL)
		return (NULL);
	cmds[0].cmd = ft_strdup("cat");
	cmds[0].args = malloc(2 * sizeof(char *));
	cmds[0].args[0] = ft_strdup("cat");
	cmds[0].args[1] = NULL;
	cmds[0].redirect = malloc(2 * sizeof(char *));
	cmds[0].redirect[0] = ft_strdup("< Makefile");
	cmds[0].redirect[1] = NULL;

	cmds[1].cmd = ft_strdup("grep");
	cmds[1].args = malloc(3 * sizeof(char *));
	cmds[1].args[0] = ft_strdup("grep");
	cmds[1].args[1] = ft_strdup("cc");
	cmds[1].args[2] = NULL;
	cmds[1].redirect = malloc(1 * sizeof(char *));
	cmds[1].redirect[0] = NULL;

	cmds[2].cmd = ft_strdup("tr");
	cmds[2].args = malloc(4 * sizeof(char *));
	cmds[2].args[0] = ft_strdup("tr");
	cmds[2].args[1] = ft_strdup("c");
	cmds[2].args[2] = ft_strdup("x");
	cmds[2].args[3] = NULL;
	cmds[2].redirect = malloc(1 * sizeof(char *));
	cmds[2].redirect[0] = NULL;
	return (cmds);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_cmd	*cmds;
	char	*line;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	if (env == NULL)
		return (EXIT_FAILURE);
	signal_prompt();
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break;
		signal_exec();
		cmds = parsing(line);
		exec(env, 3, cmds);
	}
	rl_clear_history();
	return (EXIT_SUCCESS); // return avec $?
}
