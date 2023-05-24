/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:21:47 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/24 03:42:59 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include <limits.h>
#include <stdlib.h>

static int	ft_intlen(int n)
{
	long	nb;
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	int		sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	size = ft_intlen(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size--)
	{
		str[size] = (n % 10) * sign + '0';
		n /= 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
