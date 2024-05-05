/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <imehdid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/05/05 12:21:48 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_redirs(t_astnode *root, char **redirections, int fds[2],
		t_list **env)
{
	int	empty_status;
	int	status;

	del_redirs_from_root(&root);
	empty_status = no_cmds(root);
	status = make_redirection(redirections, fds, -1, env);
	free_double_array(redirections);
	if (status == -500 || empty_status == 0)
	{
		restore_std(fds);
		if (status == -500)
			ft_putchar_fd('\n', 2);
	}
	if (empty_status == 0 && g_last_command_status != 1)
		g_last_command_status = 3;
	if (status == -500 && g_last_command_status != 131)
		g_last_command_status = 130;
}

static int	execute_command(t_astnode *node, t_list **env, int fds[2])
{
	char	**envp;

	handle_builtin(node->value, env, node, fds);
	if (g_last_command_status != 300)
		return (0);
	envp = create_envp(*env);
	if (!envp)
	{
		ft_putstr_fd("Allocation error\n", 2);
		g_last_command_status = 1;
		return (1);
	}
	if (g_last_command_status == 300)
		g_last_command_status = 0;
	launch_executable(node->value, envp, -1, fds);
	free_double_array(envp);
	return (0);
}

static void	simple_cmd(t_astnode *root, t_list **env,
	char **redirs, int fds[2])
{
	redirs = create_list(root);
	if (redirs)
		init_redirs(root, redirs, fds, env);
	if (stop_exec_cmd(fds) == 0)
	{
		restore_std(fds);
		return ;
	}
	g_last_command_status = 0;
	execute_command(root, env, fds);
	restore_std(fds);
}

void	init_executor(t_astnode *root, t_list **env)
{
	char		**redirections;
	int			fds[2];

	ft_memset(fds, -1, sizeof(fds));
	if (!backup_std(fds))
	{
		g_last_command_status = 1;
		return ;
	}
	redirections = NULL;
	g_last_command_status = 0;
	if (root->type == PIPE_NODE)
	{
		g_last_command_status = 0;
		restore_std(fds);
		if (init_pipe(root, env, 0) == 1)
		{
			ft_putstr_fd("Error occurred\n", 2);
			g_last_command_status = 1;
		}
	}
	else if (root->type == COMMAND_NODE)
		simple_cmd(root, env, redirections, fds);
}
