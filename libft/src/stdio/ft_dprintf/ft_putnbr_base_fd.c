/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:03:30 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/19 22:03:29 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int	ft_putchar_fd(char c, int fd);

int	ft_putnbr_base_fd(unsigned long long n, int fd, const char *base)
{
	unsigned int	base_len;
	int				ret;

	base_len = (unsigned int)ft_strlen(base);
	ret = 0;
	if (n >= base_len)
	{
		ret += ft_putnbr_base_fd(n / base_len, fd, base);
		ret += ft_putnbr_base_fd(n % base_len, fd, base);
	}
	else
		ret += ft_putchar_fd(base[n], fd);
	return (ret);
}
