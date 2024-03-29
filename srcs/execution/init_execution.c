/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/29 23:51:02 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	finish_init_pipe(
	t_astnode *node,
	int counter,
	char **cmds,
	t_list **env)
{
	if (node->left && node->right && node->right->type == COMMAND_NODE)
	{
		cmds[counter] = ft_strdup(node->left->value);
		cmds[counter + 1] = ft_strdup(node->right->value);
		if (cmds[counter] == NULL || cmds[counter + 1] == NULL)
		{
			ft_putstr_fd("Allocation error\n", 2);
			g_last_command_status = 1;
			free_double_array(cmds);
			return (1);
		}
	}
	if (execute_pipeline(cmds, env, node) == 1)
	{
		free_double_array(cmds);
		g_last_command_status = 1;
		return (1);
	}
	free_double_array(cmds);
	return (0);
}

static int	init_pipe(t_astnode *node, t_list **env, int counter)
{
	char	**cmds;

	cmds = ft_calloc(get_pipe_size(node) + 2, sizeof(char *));
	if (cmds == NULL)
	{
		g_last_command_status = 1;
		return (1);
	}
	while (node->right && node->right->type != COMMAND_NODE)
	{
		cmds[counter] = ft_strdup(node->left->value);
		if (cmds[counter] == NULL)
		{
			ft_putstr_fd("Allocation error\n", 2);
			free_double_array(cmds);
			g_last_command_status = 1;
			return (1);
		}
		node = node->right;
		counter++;
	}
	if (finish_init_pipe(node, counter, cmds, env) == 1)
		return (1);
	return (0);
}

static int	execute_command(t_astnode *node, char **envp, t_list **env)
{
	if (envp == NULL)
	{
		ft_putstr_fd("Allocation error\n", 2);
		g_last_command_status = 1;
		return (1);
	}
	handle_builtin(node->value, envp, env, node);
	if (g_last_command_status != 300)
	{
		free(envp);
		return (0);
	}
	if (g_last_command_status == 300)
		g_last_command_status = 0;
	launch_executable(node->value, envp, -1);
	free(envp);
	return (0);
}

void	init_redirs(t_astnode *root, char **redirections, int fds[2])
{
	int			status;
	t_astnode	*temp;

	del_redirs_from_root(&root);
	temp = root;
	while (temp)
	{
		if (only_spaces(temp->value) == 0
			|| (temp->left && only_spaces(temp->left->value) == 0))
			status = 0;
		temp = temp->right;
	}
	if (status != 0)
		status = make_redirection(redirections, fds, 0, 0);
	if (status == -500 || status == 0)
	{
		restore_std(fds);
		ft_putchar_fd('\n', 2);
		free_double_array(redirections);
	}
	if (status == 0)
		g_last_command_status = 1;
	if (status == -500)
		g_last_command_status = 130;
}

void	init_executor(t_astnode *root, t_list **env)
{
	char		**redirections;
	int			fds[2];

	g_last_command_status = 0;
	redirections = create_list(root);
	if (redirections)
	{
		init_redirs(root, redirections, fds);
		if (g_last_command_status == 130 || \
			g_last_command_status == 1)
			return ;
	}
	if (g_last_command_status == 350)
	{
		g_last_command_status = 1;
		return ;
	}
	if (root->type == PIPE_NODE)
		init_pipe(root, env, 0);
	else if (root->type == COMMAND_NODE)
		execute_command(root, create_envp(*env), env);
	restore_std(fds);
	if (redirections)
		free_double_array(redirections);
}
