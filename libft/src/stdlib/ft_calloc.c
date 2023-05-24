/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:45:45 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/24 03:42:16 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include <stdint.h>

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*res;

	if (nelem == SIZE_MAX || elsize == SIZE_MAX)
		return (NULL);
	res = malloc(nelem * elsize);
	if (!res)
		return (NULL);
	ft_bzero(res, nelem * elsize);
	return (res);
}
