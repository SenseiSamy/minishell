/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:02:54 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/19 23:06:10 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_putnbr_base_fd(unsigned long long n, int fd, const char *base);
int	ft_putstr_fd(char *s, int fd);

int	ft_putptr_fd(unsigned long long ptr, int fd)
{
	int	ret;

	ret = 0;
	ret += ft_putstr_fd("0x", fd);
	ret += ft_putnbr_base_fd(ptr, fd, "0123456789abcdef");
	return (ret);
}
