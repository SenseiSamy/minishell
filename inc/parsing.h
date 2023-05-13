/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:33:04 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/13 15:55:29 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define ARG_MAX 2048

# include "minishell.h"

/*conv_cmd*/
t_cmd		*convert_cmd(const char *line);
/*next_word*/
char		*next_word(const char *line, char str[], size_t *il);
/*libft*/
char		*ft_strjoin(const char *s1, const char *s2);
/*syntax_norm*/
bool		syntax_error(char *str);
bool		is_end(const char *str, size_t i);
bool		is_start(const char *str, size_t *i);
/*syntax*/
bool		syntax_check(const char *str);
/*var*/
bool		is_on_quote(const char *line, size_t end);
void		convert_variable(const char *line, size_t *il, char *str,
				size_t *is);

#endif