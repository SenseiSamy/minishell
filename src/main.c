/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:24:32 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/26 20:16:11 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "minishell.h"

static char	*get_prompt(void)
{
	char	*prompt;
	char	*tmp;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (is_crash(pwd))
		return (NULL);
	prompt = ft_strjoin("\033[1;32mminishell\033[0m:", pwd);
	if (is_crash(prompt))
		return (NULL);
	tmp = ft_strjoin(prompt, "$ ");
	if (is_crash(tmp))
		return (NULL);
	free(prompt);
	free(pwd);
	return (tmp);
}

void	print_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i].cmd && cmd[i].args && cmd[i].redirect)
	{
		j = 0;
		printf("cmd[%i]->cmd = %s\n", i, cmd->cmd);
		while (cmd[i].args[j])
		{
			printf("	cmd[%i]->args[%i] = %s\n", i, j, cmd[i].args[j]);
			j++;
		}
		j = 0;
		while (cmd[i].redirect[j])
		{
			printf("	cmd[%i]->redirect[%i] = %s\n", i, j, cmd[i].redirect[j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

static int	ft_prompt(t_cmd *cmds)
{
	char	*line;
	char	*prompt;

	signal_prompt();
	prompt = get_prompt();
	if (prompt == NULL)
		return (1);
	line = readline(prompt);
	free(prompt);
	if (line == NULL)
		return (1);
	if (line && line[0] == '\0')
		return (free(line), 0);
	signal_exec();
	add_history(line);
	cmds = ft_parsing(line);
	//print_cmd(cmds);
	free(line);
	if (cmds == NULL)
		return (1);
	exec(cmds);
	cleanup(cmds);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmds;
	int		status;

	(void)argc;
	(void)argv;
	cmds = NULL;
	print_mininishell();
	if (init_env(envp) == EXIT_FAILURE)
		perror2("minishell");
	while (1)
		if (ft_prompt(cmds))
			break ;
	write(2, "exit\n", 5);
	rl_clear_history();
	status = ft_atoi(env_get_var("?")->value);
	env_free();
	return (status);
}
