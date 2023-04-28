/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:33:04 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/28 02:43:24 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

// utils
char	*take_redir(const char *str, char *word, size_t *i);
char	*take_pipe(const char *str, char *word, size_t *i);
char	*conv_var(const char *str, size_t *i);
char	*ft_lstrjoin(char const *s1, char const *s2, size_t len);

// parsing
char	**ft_lsplit(const char *str);

#endif