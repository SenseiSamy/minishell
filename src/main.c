/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:24:32 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/16 14:59:11 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_exec	e;

	(void)argc;
	(void)argv;
	e.env = env_copy(envp);
	env_add(&e.env, ft_strdup("USER"), ft_strdup("LOOOL"));
	env(e.env);
	env_free(e.env);
	return (EXIT_SUCCESS);
}
