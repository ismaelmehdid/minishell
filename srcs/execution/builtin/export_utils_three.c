/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:25:19 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/28 14:57:42 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	dup_env_var(char *to, char *from)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (from[i] && from[i] != '=' && from[i] != '+')
	{
		to[j] = from[i];
		i++;
		j++;
	}
	if (from[i] == '+')
		i++;
	while (from[i])
	{
		to[j] = from[i];
		i++;
		j++;
	}
}

static int	get_var_size(char *arg)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
	{
		length++;
		i++;
	}
	if (arg[i] == '+')
		i++;
	while (arg[i])
	{
		length++;
		i++;
	}
	return (length);
}

char	*cpy_new_env(char *arg)
{
	char	*new;
	int		length;

	length = get_var_size(arg);
	new = ft_calloc(length + 1, sizeof(char));
	if (!new)
		return (NULL);
	dup_env_var(new, arg);
	return (new);
}
