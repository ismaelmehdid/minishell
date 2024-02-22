/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:49:26 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/22 15:20:58 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_astnode	*create_node(char *element)
{
	t_astnode	*node;

	node = malloc(sizeof(t_astnode));
	if (!node)
	{
		perror("Malloc problem in function create_node");
		return (NULL);
	}
	node->value = ft_strdup(element);
	node->left = NULL;
	node->right = NULL;
	node->type = get_element_type(element);
	return (node);
}

static t_astnode	*tree_init(t_astnode **root, t_astnode **curnode, char *str)
{
	t_astnode	*new_node;

	new_node = create_node(str);
	if (!new_node)
	{
		free_all_nodes(*root);
		perror("Error during the creation of a node in AST");
		return (NULL);
	}
	if (!*root)
	{
		*root = new_node;
		*curnode = new_node;
	}
	else
	{
		(*curnode)->right = new_node;
		*curnode = (*curnode)->right;
	}
	return (new_node);
}

t_astnode	*init_ast(char **elements)
{
	t_astnode	*root;
	t_astnode	*current_node;
	int			i;

	root = NULL;
	current_node = NULL;
	i = 0;
	while (elements[i])
	{
		if (!tree_init(&root, &current_node, elements[i]))
			return (NULL);
		i++;
	}
	return (root);
}

t_astnode	*parsing(char *input)
{
	char		**elements;
	t_astnode	*root;

	if (!input)
		return (NULL);
	elements = split_quotes(input, " 	\r\n\v\f");
	if (!elements)
		return (NULL);
	root = init_ast(elements);
	free_double_array(elements);
	if (!root)
		return (NULL);
	if (syntax_checker(root))
	{
		free_all_nodes(root);
		return (NULL);
	}
	return (root);
}
