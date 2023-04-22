/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:24:32 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/22 19:03:30 by snaji            ###   ########.fr       */
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
	t_cmd	*cmds;
	char	*line;
	int		status;

	(void)argc;
	(void)argv;
	if (init_env(envp) == EXIT_FAILURE)
		perror2("minishell");
	while (1)
	{
		signal_prompt();
		line = readline("minishell> ");
		if (line == NULL)
			break;
		signal_exec();
		add_history(line);
		cmds = parsing(line);
		exec(3, cmds);
	}
	rl_clear_history();
	status = ft_atoi(env_get_var("?")->value);
	env_free();
	return (status);
}
