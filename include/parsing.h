/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:35:53 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/23 18:35:28 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/*ambigus_syntax*/
bool		ambigus_syntax(const char *str);
/*conv_cmd*/
t_cmd		*convert_cmd(const char *line);
/*next_word*/
char		*next_word(const char *line, size_t *il);
/*syntax_norm*/
bool		is_on_quote(const char *line, size_t end);
bool		is_empty(const char *line);
bool		syntax_error(char *str);
bool		is_end(const char *str, size_t i);
bool		is_start(const char *str, size_t *i);
/*syntax*/
bool		syntax_check(const char *str);
/*pre_parsing*/
char		*get_name(const char *line, size_t il);
char		*pre_parsing(const char *line, bool is_heredoc);
/*size_preparsing*/
size_t		size_pre_parsing(const char *line);

#endif