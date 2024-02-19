/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:49:26 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/19 01:16:38 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

enum s_nodetype	get_element_type(char *element)
{
	char		**args;
	char		**flags;
	char		**pipes;
	char		**redirections;

	args = (char *[]){"echo", "cd", "pwd", "export"
					, "unset", "env", "exit", NULL};
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
	return (UNRECOGNIZED_NODE);
}

t_astnode *create_node(char *element)
{
	t_astnode	*node;

	node = malloc(sizeof(t_astnode));
	if (!node)
	{
		perror("Malloc problem in function create_node");
		return (NULL);
	}
	node->value = element;
	node->left = NULL;
	node->right = NULL;
	node->type = get_element_type(element);
	return (node);
}

t_astnode	*init_ast(char **elements)
{
	t_astnode	*root;
	t_astnode	*current_node;
	t_astnode	*new_node;
	int			i;
	
	root = NULL;
	current_node = NULL;
	new_node = NULL;
	i = 0;
	while (elements[i])
	{
		new_node = create_node(elements[i]);
		if (!new_node)
		{
			free_all_nodes(root);
			perror("Error during the creation of a node in AST");
			return (NULL);
		}
		if (!root)
		{
			root = new_node;
			current_node = new_node;
		}
		else
		{
			current_node->right = new_node;
			current_node = current_node->right;
		}
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
	elements = ft_split(input, ' ');
	if (!elements)
		return (NULL);
	root = init_ast(elements);
	if (!root)
	{
		free_double_array(elements);
		return (NULL);
	}
	//Check if commands are in the right order and no syntax mistakes
	return (root);
}