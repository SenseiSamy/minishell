/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 03:02:51 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/24 03:04:51 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	utils_get_str(t_str_quotes *str_quotes, t_var *input, char quote_type)
{
	if (input->str[input->i] == quote_type)
	{
		str_quotes->quote_open = !str_quotes->quote_open;
		if (str_quotes->quote_open)
			str_quotes->i = input->i + 1;
		else
		{
			ft_strncpy(str_quotes->result + str_quotes->index,
				input->str + str_quotes->i, input->i - str_quotes->i);
			str_quotes->index += input->i - str_quotes->i;
			if (input->i + 1 < str_quotes->length
				&& input->str[input->i + 1] != quote_type)
				return (1);
		}
	}
	input->i++;
	return (0);
}

t_cmd	*linked_to_array(t_cmd_linked *head)
{
	int				i;
	int				size;
	t_cmd_linked	*tmp;
	t_cmd			*array;

	i = 0;
	size = count_elements(head);
	array = (t_cmd *)ft_calloc(size + 1, sizeof(t_cmd));
	if (!array)
		return (errno = EMEM, NULL);
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
