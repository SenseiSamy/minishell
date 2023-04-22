/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:02:36 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/23 00:09:07 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t size)
{
	void	*new_ptr;

	if (size)
	{
		if (!ptr)
			return (malloc(size));
		new_ptr = malloc(size);
		if (new_ptr)
		{
			if (old_size < size)
				ft_memcpy(new_ptr, ptr, old_size);
			else
				ft_memcpy(new_ptr, ptr, size);
			free(ptr);
		}
	}
	return (new_ptr);
}
