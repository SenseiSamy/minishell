/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 02:20:54 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/12 03:40:52 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*create_command(char *cmd_str)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	new_cmd->cmd = strdup(cmd_str);
	new_cmd->args = NULL;
	new_cmd->redirect = NULL;
	new_cmd->fd_in = 0;
	new_cmd->fd_out = 1;
	new_cmd->pid = 0;
	return (new_cmd);
}

t_cmd	*add_command(t_cmd **commands, char *cmd_str)
{
	t_cmd	*new_cmd;
	t_cmd	*current;

	new_cmd = create_command(cmd_str);
	if (*commands == NULL)
		*commands = new_cmd;
	else
	{
		current = *commands;
		while (current->pid != 0)
			current = (t_cmd *)((intptr_t)current->pid);
		current->pid = (intptr_t)new_cmd;
	}
	return (new_cmd);
}

void	add_arg_to_command(t_cmd *current_cmd, char *arg_str)
{
	int	argc;

	argc = 0;
	if (current_cmd->args)
		while (current_cmd->args[argc])
			argc++;
	current_cmd->args = (char **)realloc(current_cmd->args, (argc + 2)
			* sizeof(char *));
	current_cmd->args[argc] = strdup(arg_str);
	current_cmd->args[argc + 1] = NULL;
}

t_cmd	*process_tokens(t_token *tokens, char **envp)
{
	t_cmd	*commands;
	t_cmd	*current_cmd;
	bool	new_command;

	commands = NULL;
	current_cmd = NULL;
	new_command = true;
	while (tokens && tokens->type != END)
	{
		if (tokens->type == WORD && new_command)
		{
			current_cmd = add_command(&commands, tokens->str);
			new_command = false;
		}
		else if (tokens->type == WORD && !new_command)
			add_arg_to_command(current_cmd, tokens->str);
		else if (tokens->type == DOLLAR)
		{
			handle_dollar_token(&tokens, envp);
			if (tokens->type == WORD && new_command)
			{
				current_cmd = add_command(&commands, tokens->str);
				new_command = false;
			}
			else if (tokens->type == WORD && !new_command)
				add_arg_to_command(current_cmd, tokens->str);
		}
		else if (tokens->type >= REDI_IN && tokens->type <= REDI_IN_APPEND)
			handle_redirect_token(&tokens, &current_cmd);
		else if (tokens->type == PIPE)
			new_command = true;
		tokens = tokens->next;
	}
	return (commands);
}
// TODO: erreur de norm et utiliser libft pour une fois