/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:45:45 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/20 17:32:46 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*ptr;

	ptr = malloc(nelem * elsize);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nelem * elsize);
	return (ptr);
}
