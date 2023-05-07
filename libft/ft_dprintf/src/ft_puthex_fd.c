/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:02:14 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/07 18:02:16 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_puthex_fd(unsigned int n, int fd, int upper_case)
{
	if (upper_case)
		return (ft_putnbr_base_fd(n, fd, "0123456789ABCDEF"));
	else
		return (ft_putnbr_base_fd(n, fd, "0123456789abcdef"));
}
