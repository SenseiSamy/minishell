/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 03:29:02 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/21 01:22:11 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(const char *name)
{
	const char	*value;
	size_t		length;
	char		*env_entry;

	if (name == NULL)
		return (ft_putstr_fd("unset: No variable name provided\n", 2), 1);
	value = getenv(name);
	if (value == NULL)
		return (perror("getenv"), 1);
	length = ft_strlen(name);
	env_entry = malloc(length + 2);
	if (env_entry == NULL)
		return (perror("malloc"), 1);
	ft_strcpy(env_entry, name);
	ft_strcat(env_entry, "=");
	if (putenv(env_entry) != 0)
	{
		perror("putenv");
		free(env_entry);
		return (1);
	}
	return (0);
}

/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <variable_name>\n", argv[0]);
		return (1);
	}
	return (unset(argv[1]));
}
*/