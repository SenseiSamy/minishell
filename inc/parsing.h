/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:33:04 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/16 02:44:55 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/*
Remplace les variables -> Prend en charge les string -> Recupere les redirection
-> Recupere les cmd avec les arguments
*/

typedef struct s_var
{
	char	*str;
	int		i;
	char	**envp;
}			t_var;

char	*ft_take_string(char *str, int *i);

#endif