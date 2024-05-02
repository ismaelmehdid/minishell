/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:22:13 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/30 12:40:22 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	exit_in_child(char *cmd, t_pipeline *utl,
					t_list **env)
{
	int		i;

	i = 0;
	while (is_whitespace(cmd[i]))
		i++;
	cmd += i;
	if (get_command(cmd, "exit") == 0)
	{
		execute_exit_pipe(utl, env);
		exit (g_last_command_status);
	}
}

static void	exec_in_child(t_pipeline *utl, t_list **env)
{
	char	**envp;

	exit_in_child(utl->cmds[utl->k], utl, env);
	g_last_command_status = \
		handle_builtin(utl->cmds[utl->k], env, NULL, utl->fds);
	if (g_last_command_status != 300)
	{
		full_free_child(utl, env);
		exit(g_last_command_status);
	}
	envp = create_envp(*env);
	close(utl->fds[0]);
	close(utl->fds[1]);
	launch_cmd(utl->cmds[utl->k], envp, NULL, NULL);
	full_free_child(utl, env);
	exit (g_last_command_status);
}

static void	handle_redir(t_pipeline *utl, t_list **env)
{
	char	**redirs;
	int		status;
	int		empty_status;

	redirs = ft_split(utl->redirs[utl->k], '\t');
	if (!redirs)
	{
		full_free_child(utl, env);
		exit (1);
	}
	empty_status = check_empty_status(utl->cmds[utl->k]);
	status = make_redirection(redirs, utl->fds, -1);
	free_double_array(redirs);
	if (status == -500 || empty_status == 0)
	{
		restore_std(utl->fds);
		if (status == -500)
			ft_putchar_fd('\n', 2);
	}
	if (empty_status == 0 && g_last_command_status != 1)
		g_last_command_status = 3;
	else if (status == -500)
		g_last_command_status = 130;
	stop_exec(utl, env);
}

void	child_process(t_pipeline *utl, t_list **env, t_astnode *root)
{
	free_all_nodes(root);
	if (handle_fds_dup(utl->cmds, utl) != 0)
	{
		full_free_child(utl, env);
		exit (1);
	}
	if (utl->redirs[utl->k] && (utl->redirs[utl->k][0] == '<' || \
		utl->redirs[utl->k][0] == '>'))
		handle_redir(utl, env);
	while (utl->m < 2 * utl->i)
	{
		close(utl->fd[utl->m]);
		utl->m++;
	}
	exec_in_child(utl, env);
}
