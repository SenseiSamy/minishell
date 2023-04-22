/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 02:04:19 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/21 00:33:28 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double	ft_atof(char *str)
{
	long double		res;
	long double		pow;
	int				sign;

	res = 0;
	pow = 1;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
		res = res * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str++ - '0');
		pow *= 10;
	}
	return (res * sign / pow);
}
