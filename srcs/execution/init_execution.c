/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/19 00:18:09 by imehdid          ###   ########.fr       */
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

static int	finish_init_pipe(t_astnode *node, int counter, char **cmds, t_list **env)
{
	if (node->left && node->right && node->right->type == COMMAND_NODE)
	{
		cmds[counter] = ft_strdup(node->left->value);
		cmds[counter + 1] = ft_strdup(node->right->value);
		if (cmds[counter] == NULL || cmds[counter + 1] == NULL)
		{
			ft_putstr_fd("Malloc error\n", 2);
			free_double_array(cmds);
			return (1);
		}
	}
	if (execute_pipeline(cmds, env, node) == 1)
	{
		free_double_array(cmds);
		return (1);
	}
	free_double_array(cmds);
	return (0);
}

static int	init_pipe(t_astnode *node, t_list **env)
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
			ft_putstr_fd("Malloc allocation error\n", 2);
			free_double_array(cmds);
			return (1);
		}
		node = node->right;
		counter++;
	}
	if (finish_init_pipe(node, counter, cmds, env) == 1)
		return (1);
	return (0);
}

static void	execute_command(t_astnode *node, char **envp, t_list **env)
{
	int		status;
	
	if (envp == NULL)
	{
		ft_putstr_fd("Envp malloc allocation error\n", 2);
		return ;
	}
	status = handle_builtin(node->value, envp, env, node);
	if (status != 127)
		return ;
	//printf("Launching cmd: %s\n", node->value);
	launch_executable(node->value, envp); //update exit status <<<<<<
}

int	init_executor(t_astnode *root, t_list **env)
{
	char		**redirections;
	int	fds[2];
	
	if (root == NULL)
		return (1);
	redirections = create_redirs(root);
	if (redirections)
	{
		del_redirs_from_root(&root);
		if (init_redirection(redirections, fds) == -500)
		{
			restore_std(fds);
			ft_putchar_fd('\n', 2);
			free_double_array(redirections);
			return (0);
		}
	}
	if (root->type == PIPE_NODE)
		init_pipe(root, env);
	else if (root->type == COMMAND_NODE)
		execute_command(root, create_envp(*env), env);
	restore_std(fds);
	if (redirections)
		free_double_array(redirections);
	return (0);
}