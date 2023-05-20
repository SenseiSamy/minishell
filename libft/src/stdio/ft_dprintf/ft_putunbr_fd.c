/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:02:27 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/19 21:21:55 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_putnbr_base_fd(unsigned long long n, int fd, const char *base);

int	ft_putunbr_fd(unsigned int n, int fd)
{
	return (ft_putnbr_base_fd(n, fd, "0123456789"));
}
