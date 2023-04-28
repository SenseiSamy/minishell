/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:33:04 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/28 20:14:33 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

// conv_cmd
t_cmd	*conv_cmd(const char *str);

// parsing
char	*next_word(const char *str, size_t *i);
void	print_cmd(t_cmd *cmd);

// syntax
int		syntax_check(const char *str);

// utils_conv
size_t	count_pipe(const char *str);

// utils
char	*take_redir(const char *str, char *word, size_t *i);
char	*take_pipe(const char *str, char *word, size_t *i);
void	ft_var(const char *str, size_t *i, char **word, size_t *j);

#endif