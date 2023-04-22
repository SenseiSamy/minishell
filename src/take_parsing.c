/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:44:17 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/22 20:44:33 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

t_var	*init_var(char *input_str)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	var->str = input_str;
	var->i = 0;
	return (var);
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

void	cleanup(t_return *result, t_cmd *cmd, t_var *var)
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
		clean_array(cmd[i].redirect);
		i++;
	}
	clean_array(cmd[i].args);
	clean_array(cmd[i].redirect);
	free(cmd);
	free(result);
	free(var);
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

t_cmd	*ft_parsing(char *str)
{
	t_return		*result;
	t_cmd_linked	*cmd;
	t_var			*var;
	int				i;

	var = init_var(str);
	result = ft_calloc(1, sizeof(t_return));
	i = 0;
	while (var->i < (int)ft_strlen(str))
	{
		result[i] = take_word(var);
		result = ft_realloc(result, sizeof(t_return) * (i + 2));
		i++;
	}
	result[i].str = NULL;
	if (check_parsing(result, i) == 1)
	{
		printf("Error: parsing\n");
		return (NULL);
	}
	cmd = convert_cmd(result, i);
	return (linked_to_array(cmd));
}
