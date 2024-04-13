/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/13 16:27:13 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		free_double_array(envp);
		return (0);
	}
	if (g_last_command_status == 300)
		g_last_command_status = 0;
	launch_executable(node->value, envp, -1);
	free_double_array(envp);
	return (0);
}

void	init_redirs(t_astnode *root, char **redirections, int fds[2],
		int status)
{
	int	empty_status;

	del_redirs_from_root(&root);
	empty_status = no_cmds(root);
	status = make_redirection(redirections, fds, 0, -1);
	if (status == -500 || empty_status == 0)
	{
		restore_std(fds);
		if (status == -500)
			ft_putchar_fd('\n', 2);
		free_double_array(redirections);
	}
	if (empty_status == 0 && g_last_command_status != 1)
		g_last_command_status = 3;
	if (status == -500 && g_last_command_status != 131)
		g_last_command_status = 130;
}

static int	stop_exec(void)
{
	if (g_last_command_status == 130 || \
		g_last_command_status == 3 || \
		g_last_command_status == 131)
	{
		if (g_last_command_status == 3)
			g_last_command_status = 0;
		return (0);
	}
	if (g_last_command_status == 350 || \
		g_last_command_status == 1)
	{
		g_last_command_status = 1;
		return (0);
	}
	return (1);
}

void	init_executor(t_astnode *root, t_list **env)
{
	char		**redirections;
	int			fds[2];

	ft_memset(fds, -1, sizeof(fds));
	g_last_command_status = 0;
	redirections = create_list(root);
	if (redirections)
		init_redirs(root, redirections, fds, 1);
	if (stop_exec() == 0)
		return ;
	if (root->type == PIPE_NODE)
		init_pipe(root, env, 0);
	else if (root->type == COMMAND_NODE)
		execute_command(root, create_envp(*env), env);
	if (redirections)
		free_double_array(redirections);
	restore_std(fds);
}
