/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:49:26 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/26 18:54:47 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_astnode	*create_node(char *element)
{
	t_astnode	*node;

	node = malloc(sizeof(t_astnode));
	if (!node)
	{
		ft_putstr_fd("Malloc error\n", 2);
		return (NULL);
	}
	node->value = ft_strdup(element);
	if (!node->value)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	if (ft_strcmp(element, "|"))
		node->type = PIPE_NODE;
	else
		node->type = COMMAND_NODE;
	return (node);
}

t_astnode	*init_ast(char **elements)
{
	t_astnode	*root;
	t_astnode	*pipe_node;
	t_astnode	*command_node;
	int			elements_size;

	root = NULL;
	elements_size = size_double_array(elements);
	if (elements_size == 1)
		return (create_node(elements[0]));
	elements_size--;
	while (elements_size >= 0)
	{
		if (!root)
			root = create_node(elements[elements_size]);
		else
		{
			pipe_node = create_node("|");
			command_node = create_node(elements[elements_size]);
			if (!command_node)
			{
				free_all_nodes(root);
				return (NULL);
			}
			pipe_node->right = root;
			pipe_node->left = command_node;
			root = pipe_node;
		}
		elements_size--;
	}
	return (root);
}

t_astnode	*parsing(char **input, t_list *env)
{
	t_astnode	*root;
	char		**elements;

	if (!(*input) || (*input) == NULL)
		return (NULL);
	elements = NULL;
	*input = pipes_validation(*input);
	if (!*input)
		return (NULL);
	if (quotes_validation(*input))
		return (NULL);
	elements = split_quotes(*input, "|", env);
	if (!elements || !size_double_array(elements))
	{
		free_double_array(elements);
		return (NULL);
	}
	root = init_ast(elements);
	free_double_array(elements);
	return (root);
}