/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:25:04 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/23 02:15:20 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_command_args_indexes(char *input, t_astnode *root)
{
	int	i;

	i = 0;
	while (input[i] && !(is_whitespace(input[i]) && root->quotes_indexes[root->starting_index + i] == 0))
		i++;
	return (i);
}

int	get_command(char *input, char *checking, t_astnode *root)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	j = 0;
	length = 0;
	while (input[i] && !(is_whitespace(input[i]) && root->quotes_indexes[root->starting_index + i] == 0))
	{
		if (root->quotes_indexes[root->starting_index + i] != 0 || (input[i] != '\'' && input[i] != '"'))
			length++;
		i++;
	}
	if (ft_strlen(checking) != length)
		return (-1);
	i = 0;
	while (j < length)
	{
		if (root->quotes_indexes[root->starting_index + i] == 0 && (input[i] == '\'' || input[i] == '"'))
		{
			i++;
			continue ;
		}
		if (input[i] != checking[j])
			return (-1);
		j++;
		i++;
	}
	return (0);
}