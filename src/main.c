/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:24:32 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/22 04:10:47 by cfrancie         ###   ########.fr       */
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

void	clean_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
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
	i = 0;
	while (cmd[i].cmd != NULL)
	{
		free(cmd[i].cmd);
		clean_array(cmd[i].args);
		clean_array(cmd[i].redir);
		i++;
	}
	clean_array(cmd[i].args);
	clean_array(cmd[i].redir);
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
		array[i].redir = head->redir;
		tmp = head;
		head = head->next;
		free(tmp);
		i++;
	}
	return (array);
}

int	main(void)
{
	t_var			*var;
	t_cmd_linked	*cmd;
	t_cmd			*tab;
	char			*input_str;
	int				size;
	int				i;

	t_return (*result);
	input_str = ft_strdup("echo \"test\" << ahah >> bba | cat -e | wc -l | > test.txt");
	var = init_var(input_str);
	result = ft_calloc(1, sizeof(t_return));
	var->envp = (char **)ft_calloc(2, sizeof(char *));
	var->envp[0] = "test=42";
	var->envp[1] = NULL;
	i = 0;
	while (var->i < (int)ft_strlen(input_str))
	{
		result[i] = take_word(var);
		display_result(result[i]);
		result = ft_realloc(result, sizeof(t_return) * (i + 2));
		i++;
	}
	result[i].str = NULL;
	size = i;
	cmd = convert_cmd(result, size);
	printf("--------------------\n");
	i = 0;
	tab =  linked_to_array(cmd);
	while (tab[i].cmd != NULL || tab[i].args != NULL || tab[i].redir != NULL)
	{
		display_cmd(&tab[i]);
		i++;
	}
	cleanup(result, var, input_str, tab);
	return (0);
}
