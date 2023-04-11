/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:57:30 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/11 18:54:38 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

typedef struct s_redirect
{
	char						*type;
	char						*file;
	typedef struct s_redirect	*next;
}								t_redirect;

static size_t	size_word(char *str, int *i)
{
	size_t	size;

	size = 0;
	while (ft_isspace(str[*i]))
		*i++;
	if (str[*i] == '<' || str[*i] == '>')
	{
		if (str[*i + 1] == '<' || str[*i + 1] == '>')
			return (2);
		else
			return (1);
	}
	while (str[*i] && !ft_isspace(str[*i]))
	{
		size++;
		*i++;
	}
	return (size);
}

static void	assign_type(t_redirect *red, char *str, size_t *i)
{
	if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			red->type = ft_strdup("<<");
			*i++;
		}
		else
			red->type = ft_strdup("<");
		*i++;
	}
	else
	{
		if (str[*i + 1] == '>')
		{
			red->type = ft_strdup(">>");
			*i++;
		}
		else
			red->type = ft_strdup(">");
		*i++;
	}
}

static void	assign_file(t_redirect *red, char *str, size_t *i)
{
	size_t	size;

	size = size_word(str, i);
	red->file = malloc(sizeof(char) * (size + 1));
	if (!red->file)
		exit(1);
	ft_strlcpy(red->file, str + *i, size + 1);
	*i += size;
}

static char	**convert_struct_to_tab(t_redirect *red)
{
	char	**result;
	size_t	i;

	i = 0;
	result = malloc(sizeof(char *) * (ft_lstsize(red) + 1));
	if (!result)
		return (NULL);
	while (red)
	{
		result[i] = ft_strjoin(red->type, " ");
		if (!result[i])
			return (NULL);
		result[i] = ft_strjoin(result[i], red->file);
		if (!result[i])
			return (NULL);
		red = red->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_get_redirect(char *str)
{
	t_redirect	*result;
	size_t		i;

	i = 0;
	result = malloc(sizeof(t_redirect));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			assign_type(result, str, &i);
			assign_file(result, str, &i);
			result->next = malloc(sizeof(t_redirect));
			if (!result->next)
				return (NULL);
			result = result->next;
		}
		i++;
	}
	return (convert_struct_to_tab(result));
}

int	main(void)
{
	char	*str;
	char	**result;

	str = "<    Makefile <<<< <>";
	result = ft_get_redirect(str);
	for (int i = 0; result[i]; i++)
	{
		printf("%s\n", result[i]);
		free(result[i]);
	}
	free(result);
	return (0);
}
