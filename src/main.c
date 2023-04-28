/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:24:32 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/28 02:51:34 by cfrancie         ###   ########.fr       */
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
	if (cmd == NULL)
	{
		printf("cmd = NULL\n");
		return ;
	}
	while (cmd[i].cmd != NULL && cmd[i].args != NULL && cmd[i].redirect != NULL)
	{
		j = -1;
		printf("cmd[%i]->cmd = {%s}\n", i, cmd->cmd);
		while (cmd[i].args[++j])
			printf("  cmd[%i]->args[%i] = {%s}\n", i, j, cmd[i].args[j]);
		j = -1;
		while (cmd[i].redirect[++j])
			printf("  cmd[%i]->redirect[%i] = {%s}\n", i, j, cmd[i].redirect[j]);
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
	if (line && line[0] == '\0')
		return (free(line), 0);
	if (line == NULL)
		return (1);
	signal_exec();
	add_history(line);
	cmds = ft_parsing(line);
	print_cmd(cmds);
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
	rl_clear_history();
	status = ft_atoi(env_get_var("?")->value);
	env_free();
	return (status);
}
