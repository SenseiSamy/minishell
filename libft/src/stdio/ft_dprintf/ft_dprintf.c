/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:51:39 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/19 22:51:11 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

int			ft_putchar_fd(char c, int fd);
int			ft_puthex_fd(unsigned int n, int fd, int upper_case);
int			ft_putnbr_fd(int n, int fd);
int			ft_putptr_fd(unsigned long long ptr, int fd);
int			ft_putstr_fd(char *s, int fd);
int			ft_putunbr_fd(unsigned int n, int fd);

static void	process_conversion(char c, va_list args, int fd, int *ret)
{
	if (c == 'c')
		*ret += ft_putchar_fd(va_arg(args, int), fd);
	else if (c == 's')
		*ret += ft_putstr_fd(va_arg(args, char *), fd);
	else if (c == 'p')
		*ret += ft_putptr_fd(va_arg(args, unsigned long long), fd);
	else if (c == 'd' || c == 'i')
		*ret += ft_putnbr_fd(va_arg(args, int), fd);
	else if (c == 'u')
		*ret += ft_putunbr_fd(va_arg(args, unsigned int), fd);
	else if (c == 'x')
		*ret += ft_puthex_fd(va_arg(args, unsigned int), fd, 0);
	else if (c == 'X')
		*ret += ft_puthex_fd(va_arg(args, unsigned int), fd, 1);
	else if (c == '%')
		*ret += ft_putchar_fd('%', fd);
	else
		*ret += ft_putchar_fd(c, fd);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	args;
	int		ret;
	char	c;

	ret = 0;
	va_start(args, str);
	c = *str++;
	while (c)
	{
		if (c == '%')
		{
			c = *str++;
			process_conversion(c, args, fd, &ret);
		}
		else
		{
			ft_putchar_fd(c, fd);
			ret++;
		}
		c = *str++;
	}
	va_end(args);
	return (ret);
}
