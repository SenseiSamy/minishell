/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:24:32 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/15 02:56:19 by cfrancie         ###   ########.fr       */
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

	pwd = ft_strdup(env_get_value("PWD"));
	if (pwd == NULL)
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
			return (NULL);
	}
	prompt = ft_strjoin("\001\e[1;32m\002minishell\001\e[0m\002:\001\e[1;34m"
			"\002", pwd);
	if (is_crash(prompt))
		return (NULL);
	tmp = ft_strjoin(prompt, "$ \001\e[0m\002");
	if (is_crash(tmp))
		return (NULL);
	free(prompt);
	free(pwd);
	return (tmp);
}

static void	utils_prompt(char *line, t_cmd *cmds)
{
	if (syntax_check(line) || ambigus_syntax(line))
		return ;
	cmds = convert_cmd(line);
	if (cmds == NULL)
		return ;
	exec(cmds);
	cleanup(cmds);
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
	utils_prompt(line, cmds);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmds;
	int		status;

	(void)argc;
	(void)argv;
	cmds = NULL;
	rl_outstream = stderr;
	print_mininishell();
	if (init_env(envp) == EXIT_FAILURE)
		perror2("minishell");
	while (1)
		if (ft_prompt(cmds))
			break ;
	write(2, "exit\n", 5);
	rl_clear_history();
	status = ft_atoi(env_get_value("?"));
	env_free();
	return (status);
}
