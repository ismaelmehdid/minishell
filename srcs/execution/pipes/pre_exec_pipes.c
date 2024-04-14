/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:47:46 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/13 14:47:49 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

int	init_pipe(t_astnode *node, t_list **env, int counter)
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
