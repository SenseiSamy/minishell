/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:33:04 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/04 18:19:22 by cfrancie         ###   ########.fr       */
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
bool	on_quote(const char *str, size_t i_str);
size_t	count_pipe(const char *str);

// utils
char	*take_redir(const char *str, char *word, size_t *i);
char	*take_pipe(const char *str, char *word, size_t *i);
void	ft_var(const char *str, size_t *i, char **word, size_t *j);

// utils_var
size_t	calcule_res_size(const char *str);

// var_pars
char	*get_name(const char *str, size_t i);
char	*var_conv(const char *str);

#endif