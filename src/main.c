/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:24:32 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/22 19:42:07 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "minishell.h"

/*
void	cleanup(t_return *result, t_var *var, char *input_str, t_cmd *cmd)
{
	t_cmd	*cmds;
	char	*line;
	int		status;

	i = 0;
	while (result[i].str != NULL)
	{
		free(result[i].str);
		i++;
	}
	i = 0;
	while (cmd[i].cmd != NULL)
	{
		free(cmd[i].cmd);
		clean_array(cmd[i].args);
		clean_array(cmd[i].redirect);
		i++;
	}
	clean_array(cmd[i].args);
	clean_array(cmd[i].redirect);
	free(cmd);
	free(var->envp);
	free(result);
	free(var);
	free(input_str);
}

int	count_elements(t_cmd_linked *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

t_cmd	*linked_to_array(t_cmd_linked *head)
{
	int		i;
	int		size;
	t_cmd_linked	*tmp;
	t_cmd	*array;

	i = 0;
	size = count_elements(head);
	array = (t_cmd *)ft_calloc(size + 1, sizeof(t_cmd));
	if (!array)
	{
		return (NULL);
	}
	while (head)
	{
		array[i].cmd = head->cmd;
		array[i].args = head->args;
		array[i].redirect = head->redir;
		tmp = head;
		head = head->next;
		free(tmp);
		i++;
	}
	return (array);
}
*/
int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmds;
	char	*line;
	int		status;

	(void)argc;
	(void)argv;
	cmds = NULL;
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