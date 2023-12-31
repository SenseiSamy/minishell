/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispunct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:35:18 by cfrancie          #+#    #+#             */
/*   Updated: 2023/05/20 17:26:49 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ispunct(int c)
{
	return ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || \
	(c >= 91 && c <= 96) || (c >= 123 && c <= 126));
}
