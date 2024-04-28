/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:22:13 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/28 19:03:49 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	exit_in_child(char *cmd,
				t_pipeline *utl,
				t_list **env, 
				t_astnode *root)
{
	int		i;

	i = 0;
	while (is_whitespace(cmd[i]))
		i++;
	cmd += i;
	if (get_command(cmd, "exit") == 0)
	{
		perror("im here");
		free_double_array(utl->cmds);
		free_pipeline_util(utl);
		execute_exit(cmd + 5, env, root, NULL);
		exit (g_last_command_status);
	}
}

static void exec_in_child(t_pipeline *utl, t_list **env, t_astnode *root)
{
	char    **envp;

	exit_in_child(utl->cmds[utl->k], utl, env, root);
	g_last_command_status = 
		handle_builtin(utl->cmds[utl->k], env, root, utl->fds);
	if (g_last_command_status != 300)
	{
		free_child_if_builtin(utl, env, root);
		exit(g_last_command_status);
	}
	envp = create_envp(*env);
	close(utl->fds[0]);
	close(utl->fds[1]);
	launch_cmd(utl->cmds[utl->k], envp, NULL, NULL);
}

static void	handle_redir(t_pipeline *utl, t_list **env, t_astnode *root)
{
	char	**redirs;
	int		status;
	int		empty_status;

	redirs = ft_split(utl->redirs[utl->k], '\t');
	if (!redirs)
	{
		free_pipeline_util(utl);
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
	stop_exec(utl, env, root);
}

void	child_process(t_pipeline *utl, t_list **env, t_astnode *root)
{
	if (handle_fds_dup(utl->cmds, utl) != 0)
	{
		free_pipeline_util(utl);
		exit (1);
	}
	if (utl->redirs[utl->k] && (utl->redirs[utl->k][0] == '<' || \
		utl->redirs[utl->k][0] == '>'))
		handle_redir(utl, env, root);
	while (utl->m < 2 * utl->i)
	{
		close(utl->fd[utl->m]);
		utl->m++;
	}
	exec_in_child(utl, env, root);
}