/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:44:17 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/24 02:12:28 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

t_var	*init_var(char *input_str)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	if (!var)
		return (errno = EMEM, NULL);
	var->str = input_str;
	var->i = 0;
	return (var);
}

static t_return	*ft_realloc_ret(t_return *result, int curr_size, int new_size)
{
	t_return	*new;
	int			i;

	i = 0;
	new = (t_return *)ft_calloc(new_size, sizeof(t_return));
	if (!new)
		return (errno = EMEM, NULL);
	while (i < curr_size)
	{
		new[i].str = result[i].str;
		new[i].i = result[i].i;
		new[i].on_quote = result[i].on_quote;
		i++;
	}
	free(result);
	return (new);
}

static void	ft_clean(t_return *ret, t_var *var)
{
	int	i;

	i = 0;
	while (ret[i].str != NULL)
	{
		free(ret[i].str);
		i++;
	}
	free(ret);
	free(var);
}

t_cmd	*ft_parsing(char *str)
{
	t_return		*result;
	t_cmd			*cmds;
	t_var			*var;
	int				i;
	int				size;

	i = 0;
	size = 1;
	var = init_var(str);
	result = ft_calloc(1, sizeof(t_return));
	if (!result)
		return (errno = EMEM, NULL);
	while (var->i < (int)ft_strlen(str))
	{
		result[i] = take_word(var);
		size++;
		result = ft_realloc_ret(result, size - 1, size);
		i++;
	}
	result[i].str = NULL;
	if (check_parsing(result, i) == 1)
		return (NULL);
	cmds = linked_to_array(convert_cmd(result, i));
	ft_clean(result, var);
	return (cmds);
}
