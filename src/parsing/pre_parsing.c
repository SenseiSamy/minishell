/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:34:04 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/12 18:32:27 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*create_token(char *str, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->str = str;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

t_token	*add_token(t_token *list, char *str, t_token_type type)
{
	t_token	*new_token;
	t_token	*current;

	new_token = create_token(str, type);
	if (list == NULL)
		return (new_token);
	current = list;
	while (current->next)
		current = current->next;
	current->next = new_token;
	return (list);
}

t_token_type	get_token_type(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (REDI_IN);
	if (ft_strcmp(str, ">") == 0)
		return (REDI_OUT);
	if (ft_strcmp(str, ">>") == 0)
		return (REDI_OUT_APPEND);
	if (ft_strcmp(str, "<<") == 0)
		return (REDI_IN_APPEND);
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	return (WORD);
}

char	*copy_substring(char *str, int start, int end)
{
	char	*substring;

	substring = (char *)malloc(end - start + 2);
	ft_memcpy(substring, &str[start], end - start + 1);
	substring[end - start + 1] = '\0';
	return (substring);
}

t_token	*pre_parsing(char *line, char **envp)
{
	t_var	var;

	var = (t_var){NULL, 0, 0, false, '\0'};
	while (line[var.i])
	{
		handle_quotes(&var, line);
		handle_space(&var, line);
		handle_dollar(&var, line);
		handle_end_of_line(&var, line);
		var.i++;
	}

	var.tokens = add_token(var.tokens, NULL, END);
	return (var.tokens);
}
