/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 00:09:18 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/19 19:47:38 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free (array);
}

void	free_all_nodes(t_astnode *root)
{
	if (!root)
		return ;
	free_all_nodes(root->left);
	free_all_nodes(root->right);
	free(root->value);
	free(root);
}

int	ft_strcmp(char *one, char *two)
{
	int	i;

	i = 0;
	if (ft_strlen(one) != ft_strlen(two))
		return (0);
	while (one[i])
	{
		if (one[i] != two[i])
			return (0);
		i++;
	}
	return (1);
}

int	contain_str(char **array, char *element)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strcmp(element, array[i]))
			return (1);
		i++;
	}
	return (0);
}

enum s_nodetype	get_element_type(char *element)
{
	char		**args;
	char		**flags;
	char		**pipes;
	char		**redirections;

	args = (char *[]){"echo", "cd", "pwd", "export",
		"unset", "env", "exit", NULL};
	flags = (char *[]){"-n", NULL};
	pipes = (char *[]){"|", NULL};
	redirections = (char *[]){"<", ">", "<<", ">>", NULL};
	if (contain_str(args, element))
		return (COMMAND_NODE);
	else if (contain_str(flags, element))
		return (FLAG_NODE);
	else if (contain_str(pipes, element))
		return (PIPE_NODE);
	else if (contain_str(redirections, element))
		return (REDIRECTION_NODE);
	return (ARGUMENT_NODE);
}
