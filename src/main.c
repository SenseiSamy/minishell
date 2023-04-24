/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:24:32 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/24 01:52:41 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "minishell.h"

void	clean_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	cleanup(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].cmd)
	{
		free(cmd[i].cmd);
		clean_array(cmd[i].args);
		clean_array(cmd[i].redirect);
		i++;
	}
	free(cmd);
}

static int	ft_prompt(t_cmd *cmds)
{
	char	*line;

	signal_prompt();
	line = readline("\033[1;32mminishell\033[0m$ ");
	if (line == NULL)
		return (free(line), 1);
	signal_exec();
	add_history(line);
	cmds = ft_parsing(line);
	free(line);
	if (cmds == NULL)
		return (2);
	exec(cmds);
	cleanup(cmds);
	return (0);
}	

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmds;
	int		status;
	int		ret;

	(void)argc;
	(void)argv;
	cmds = NULL;
	if (init_env(envp) == EXIT_FAILURE)
		perror2("minishell");
	while (1)
	{
		ret = ft_prompt(cmds);
		if (ret == 1)
			break ;
		else if (ret == 2)
			continue ;
	}
	rl_clear_history();
	status = ft_atoi(env_get_var("?")->value);
	env_free();
	return (status);
}
