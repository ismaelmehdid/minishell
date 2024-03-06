/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:49:26 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/03 15:46:14 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	*quotes_indexing(char *element)
{
	int		*quotes_indexes;
	int		i;
	char	quote;

	i = 0;
	quotes_indexes = calloc(ft_strlen(element), sizeof(int));
	if (!quotes_indexes)
		return (NULL);
	while (element[i])
	{
		if (element[i] == '\'' || element[i] == '"')
		{
			quote = element[i];
			i++;
			while (element[i] && element[i] != quote)
			{
				if (quote == '\'')
					quotes_indexes[i] = 1;
				else if (quote == '"')
					quotes_indexes[i] = 2;
				i++;
			}
		}
		quotes_indexes[i] = 0;
		i++;
	}
	return (quotes_indexes);
}

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
	if (!node->value)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->quotes_indexes = NULL;
	if (ft_strcmp(element, "|"))
		node->type = PIPE_NODE;
	else
	{
		node->type = COMMAND_NODE;
		node->quotes_indexes = quotes_indexing(element);
		if (!node->quotes_indexes)
			return (NULL);
	}
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

t_astnode	*parsing(char **input)
{
	t_astnode	*root;
	char		**elements;

	if (!*input)
		return (NULL);
	elements = NULL;
	*input = pipes_validation(*input);
	if (!*input)
		return (NULL);
	elements = split_quotes(*input, "|");
	if (!elements || !size_double_array(elements) || quotes_validation(elements))
	{
		free_double_array(elements);
		return (NULL);
	}
	if (!elements)
		return (NULL);
	root = init_ast(elements);
	free_double_array(elements);
	if (!root)
		return (NULL);
	/*
	if (syntax_checker(root))
	{
		free_all_nodes(root);
		return (NULL);
	}
	*/
	return (root);
}
