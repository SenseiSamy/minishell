/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 03:53:35 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/19 03:49:43 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
/*
void	ft_free(t_var *var, t_return *ret, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		free(ret[i].str);
		i++;
	}
	free(ret);
	free(var->envp);
}

void	print_return(t_return *ret, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		printf("------\n");
		printf("str = %s$\n", ret[i].str);
		printf("i = %d\n", ret[i].i);
		printf("on_quote = %s\n", ret[i].on_quote ? "Oui" : "Non");
		i++;
	}
	printf("------\n");
}

void	print_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i].cmd != NULL)
	{
		printf("------\n");
		printf("cmd = %s$\n", cmd[i].cmd);
		j = 0;
		while (cmd[i].args[j] != NULL)
		{
			printf("args = %s$\n", cmd[i].args[j]);
			j++;
		}
		j = 0;
		while (cmd[i].redir[j] != NULL)
		{
			printf("redir = %s$\n", cmd[i].redir[j]);
			j++;
		}
		i++;
	}
	printf("------\n");
}

int	main(void)
{
	t_var	var;
	int		i;
	int		tmp;

	t_return (*ret);
	i = 0;
	var.str = "echo < |";
	var.i = 0;
	var.envp = malloc(sizeof(char *) * 2);
	var.envp[0] = "HOME=testqsd";
	var.envp[1] = NULL;
	ret = malloc(sizeof(t_return) * 10);
	//printf("INITIAL\n");
	while (var.str[var.i] != '\0')
	{
		ret[i] = take_word(&var);
		// printf("str = %s$\n", ret[i].str);
		// printf("i = %d\n", ret[i].i);
		// printf("on_quote = %s\n", ret[i].on_quote ? "Oui" : "Non");
		// printf("------\n");
		var.i = ret[i].i;
		i++;
	}
	tmp = i;
	if (check_parsing(ret, tmp) == -1)
		return (1);
	print_return(ret, tmp);
	// t_cmd   *cmd;
	// i = 0;
	// cmd = convert_cmd(ret, tmp);
	// print_cmd(cmd);
	ft_free(&var, ret, tmp);
	return (0);
}
*/