/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:04:05 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/07 18:12:34 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>

size_t	ft_strlen(const char *s);
int		ft_putchar_fd(char c, int fd);
int		ft_puthex_fd(unsigned int n, int fd, int upper_case);
int		ft_putnbr_base_fd(unsigned long long n, int fd, const char *base);
int		ft_putnbr_fd(int n, int fd);
int		ft_putptr_fd(unsigned long long ptr, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putunbr_fd(unsigned int n, int fd);

#endif