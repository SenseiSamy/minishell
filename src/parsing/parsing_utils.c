/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 03:22:03 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/12 03:39:32 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_env_var_value(char *var_name, char **envp)
{
	int		i;
	size_t	name_len;

	i = 0;
	name_len = strlen(var_name);
	while (envp[i])
	{
		if (strncmp(envp[i], var_name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (&envp[i][name_len + 1]);
		i++;
	}
	return (NULL);
}

void	handle_dollar_token(t_token **token, char **envp)
{
	t_token	*next_token;
	char	*value;
	t_token	*to_remove;

	next_token = (*token)->next;
	if (next_token && next_token->type == WORD)
	{
		value = get_env_var_value(next_token->str, envp);
		if (value)
		{
			free((*token)->str);
			(*token)->str = strdup(value);
			(*token)->type = WORD;
			to_remove = next_token;
			(*token)->next = next_token->next;
			free(to_remove->str);
			free(to_remove);
		}
	}
	else
		(*token)->type = WORD;
}

void	handle_redirect_token(t_token **token, t_cmd **current_cmd)
{
	t_token	*next_token;
	char	*new_str;
	int		redirect_type;
	int		redirect_count;
	t_token	*to_remove;

	next_token = (*token)->next;
	if (next_token && next_token->type == WORD)
	{
		new_str = malloc(strlen((*token)->str) + strlen(next_token->str) + 2);
		strcpy(new_str, (*token)->str);
		strcat(new_str, " ");
		strcat(new_str, next_token->str);
		redirect_type = (*token)->type;
		redirect_count = 0;
		if ((*current_cmd)->redirect)
			while ((*current_cmd)->redirect[redirect_count])
				redirect_count++;
		(*current_cmd)->redirect = (char **)realloc((*current_cmd)->redirect,
				(redirect_count + 2) * sizeof(char *));
		(*current_cmd)->redirect[redirect_count] = new_str;
		(*current_cmd)->redirect[redirect_count + 1] = NULL;
		to_remove = next_token;
		(*token)->next = next_token->next;
		free(to_remove->str);
		free(to_remove);
	}
}
