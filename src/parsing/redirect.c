/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:57:30 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/11 02:16:08 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

typedef struct s_redirect
{
	char	*str;
	int		(*f)(char *str);
}				t_redirect;


char	**ft_get_redirect(char *str)
{
	char	**result;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	result = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			result[j] = malloc(sizeof(char) * (ft_strlen(str) + 1));
			while (str[i] == '<' || str[i] == '>')
			{
				result[j][k] = str[i];
				i++;
				k++;
			}
			result[j][k] = '\0';
			j++;
			k = 0;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}

int	main(void)
{
	char *str = "<    Makefile <<<< <>";
	char **result = ft_get_redirect(str);

	for (int i = 0; result[i]; i++)
	{
		printf("%s\n", result[i]);
		free(result[i]);
	}
	free(result);

	return (0);
}
