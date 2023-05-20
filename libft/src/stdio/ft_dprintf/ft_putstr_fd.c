/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:03:10 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/19 22:03:58 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_string.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = (int)ft_strlen(s);
	write(fd, s, ft_strlen(s));
	return (len);
}
