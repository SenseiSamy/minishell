/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdlib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:43:14 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/20 17:38:54 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDLIB_H
# define FT_STDLIB_H

# include <stdlib.h>

int			ft_atoi(const char *nptr);
long		ft_atol(const char *nptr);
long long	ft_atoll(const char *nptr);
void		*ft_calloc(size_t nelem, size_t elsize);
void		*ft_realloc(void *ptr, size_t size);
char		*ft_strdup(const char *s);

#endif