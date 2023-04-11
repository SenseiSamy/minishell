/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:13:31 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/11 19:14:09 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(int error_value, char *error_msg)
{
	if (error_msg)
		ft_putstr_fd(error_msg, STDERR_FILENO);
	exit(error_value);
}
