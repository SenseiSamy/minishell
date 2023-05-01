/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:24:32 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/30 19:41:26 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "minishell.h"

void	print_cmd(t_cmd *cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmd[i].cmd && cmd[i].redirect)
	{
		if (cmd[i].cmd)
			printf("cmd[%zu]: %s\n", i, cmd[i].cmd);
		j = -1;
		while (cmd[i].args[++j])
			if (cmd[i].args[j])
				printf(" args[%zu]: %s\n", j, cmd[i].args[j]);
		j = -1;
		while (cmd[i].redirect[++j])
			if (cmd[i].redirect[j])
				printf(" redirect[%zu]: %s\n", j, cmd[i].redirect[j]);
		++i;
	}
}

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

static int	isampty(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && isspace(str[i]))
		++i;
	return (!str[i]);
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
	if (!line)
		return (free(prompt), 1);
	if (line[0] == '\0')
		return (free(prompt), 0);
	free(prompt);
	signal_exec();
	add_history(line);
	if (!isampty(line) && !syntax_check(line))
	{
		cmds = conv_cmd(line);
		exec(cmds);
		cleanup(cmds);
	}
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
