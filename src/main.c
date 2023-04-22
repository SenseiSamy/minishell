/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:24:32 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/22 19:13:49 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
