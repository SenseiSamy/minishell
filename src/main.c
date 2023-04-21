/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:24:32 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/21 16:35:53 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"


t_var	*init_var(char *input_str)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	var->str = input_str;
	var->i = 0;
	return (var);
}

void	display_result(t_return result)
{
	printf("--------------------\n");
	printf("Résultat: %s$\n", result.str);
	printf("Index: %d\n", result.i);
	printf("Quote: %d\n", result.on_quote);
}

void	display_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("--------------------\n");
	printf("Commande: %s\n", cmd->cmd);
	printf("Arguments:\n");
	while (cmd->args[i] != NULL)
	{
		printf("  %s$\n", cmd->args[i]);
		i++;
	}
	i = 0;
	printf("Redirections:\n");
	while (cmd->redir[i] != NULL)
	{
		printf("  %s$\n", cmd->redir[i]);
		i++;
	}
}

void	cleanup(t_return *result, t_var *var, char *input_str, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (result[i].str != NULL)
	{
		free(result[i].str);
		i++;
	}
	//free_cmd_linked(cmd);
	i = 0;
	while (cmd[i].cmd != NULL)
	{
		free(cmd[i].cmd);
		free(cmd[i].args);
		free(cmd[i].redir);
		i++;
	}
	free(cmd);
	free(var->envp);
	free(result);
	free(var);
	free(input_str);
}

// convert an linked list of t_cmd to an array of t_cmd
t_cmd	*tinked_to_tab(t_cmd_linked *cmd)
{
	t_cmd	*tab;
	int		i;

	i = 0;
	while (cmd->next != NULL)
	{
		cmd = cmd->next;
		i++;
	}
	tab = (t_cmd *)malloc(sizeof(t_cmd) * (i + 1));
	i = 0;
	while (cmd->next != NULL)
	{
		tab[i].cmd = cmd->cmd;
		tab[i].args = cmd->args;
		tab[i].redir = cmd->redir;
		cmd = cmd->next;
		i++;
	}
	tab[i].cmd = NULL;
	tab[i].args = NULL;
	tab[i].redir = NULL;
	return (tab);
}

int	main(void)
{
	t_return		*result;
	t_var			*var;
	t_cmd_linked	*cmd;
	t_cmd			*tab;
	char			*input_str;
	int				size;
	int				i;

	input_str = strdup("echo \"test\" << ahah >> bba | cat -e | wc -l | > test.txt");
	var = init_var(input_str);
	result = calloc(1, sizeof(t_return));
	var->envp = (char **)calloc(2, sizeof(char *));
	var->envp[0] = "test=42";
	var->envp[1] = NULL;
	i = 0;
	while (var->i < (int)strlen(input_str))
	{
		result[i] = take_word(var);
		display_result(result[i]);
		result = realloc(result, sizeof(t_return) * (i + 2));
		i++;
	}
	result[i].str = NULL;
	size = i;
	cmd = convert_cmd(result, size);
	printf("--------------------\n");
	i = 0;
	tab = tinked_to_tab(cmd);
	while (tab[i].cmd != NULL)
	{
		display_cmd(&tab[i]);
		i++;
	}
	cleanup(result, var, input_str, tab);
	return (0);
}
