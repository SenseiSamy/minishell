/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:02:54 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/08 19:19:56 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_putptr_fd(unsigned long long ptr, int fd)
{
	int	ret;

	ret = 0;
	ret += ft_putstr_fd("0x", fd);
	ret += ft_putnbr_base_fd(ptr, fd, "0123456789abcdef");
	return (ret);
}
