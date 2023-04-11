/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:54:47 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/11 18:55:22 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

typedef struct s_cmd_args
{
	char						*path;
	char						*arg;
	typedef struct s_cmd_args	*next;
}								t_cmd_args;



static void	assign_path(t_cmd_args *cmd, char *str, size_t *i)
{

}