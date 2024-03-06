/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/03 19:25:03 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_pipe_size(t_astnode *node)
{
	int			counter;
	t_astnode	*tmp_node;

	counter = 1;
	tmp_node = node;
	while (tmp_node->right && tmp_node->right->type == PIPE_NODE)
	{
		tmp_node = tmp_node->right;
		counter++;
	}
	return (counter);
}

static int	finish_init_pipe(t_astnode *node, int counter, char **cmds)
{
	if (node->left && node->right && node->right->type == COMMAND_NODE)
	{
		cmds[counter] = ft_strdup(node->left->value);
		cmds[counter + 1] = ft_strdup(node->right->value);
		if (cmds[counter] == NULL || cmds[counter + 1] == NULL)
		{
			printf("Malloc error in finish_init_pipe\n");
			free_double_array(cmds);
			return (1);
		}
	}
	if (execute_pipeline(cmds) == 1)
	{
		free_double_array(cmds);
		return (1);
	}
	free_double_array(cmds);
	return (0);
}

static int	init_pipe(t_astnode *node)
{
	int		counter;
	char	**cmds;

	cmds = ft_calloc(get_pipe_size(node) + 2, sizeof(char *));
	if (cmds == NULL)
		return (1);
	counter = 0;
	while (node->right && node->right->type != COMMAND_NODE)
	{
		cmds[counter] = ft_strdup(node->left->value);
		if (cmds[counter] == NULL)
		{
			printf("Malloc error in init_pipe\n");
			free_double_array(cmds);
			return (1);
		}
		node = node->right;
		counter++;
	}
	if (finish_init_pipe(node, counter, cmds) == 1)
		return (1);
	return (0);
}

static void	execute_command(t_astnode *node, char **envp, t_list **env, t_astnode *root)
{
	int	status;

	status = handle_builtin(node->value, envp, env, root);
	if (status != 1)
		return ;
	printf("Launching cmd: %s\n", node->value);
	launch_executable(node->value, envp);
}

int	init_executor(t_astnode *root, t_list **env)
{
	t_astnode	*working_root;
	char		**envp;

	if (root == NULL)
		return (1);
	envp = create_envp(*env);
	if (envp == NULL)
	{
		ft_putstr_fd("Envp malloc allocation error\n", 2);
		return (1);
	}
	working_root = root;
	if (working_root->type == PIPE_NODE)
		init_pipe(root);
	else if (working_root->type == COMMAND_NODE)
		execute_command(root, envp, env, root);
	return (0);
}