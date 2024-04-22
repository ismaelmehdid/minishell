/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/22 14:48:22 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	handle_redir(t_pipeline *utl)
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
	status = make_redirection(redirs, utl->fds, 0, -1);
	free_double_array(redirs);
	if (status == -500 || empty_status == 0)
	{
		restore_std(utl->fds);
		if (status == -500)
			ft_putchar_fd('\n', 2);
	}
	if (empty_status == 0 && g_last_command_status != 1)
		g_last_command_status = 3;
	if (status == -500)
		g_last_command_status = 130;
	stop_exec(utl);
}

static int	child_process(t_pipeline *utl, t_list **env, t_astnode *root)
{
	char	**envp;

	envp = create_envp(*env);
	if (handle_fds_dup(utl->cmds, utl) != 0)
	{
		free_pipeline_util(utl);
		exit (1);
	}
	if (utl->redirs[utl->k] && (utl->redirs[utl->k][0] == '<' || \
		utl->redirs[utl->k][0] == '>'))
		handle_redir(utl);
	while (utl->m < 2 * utl->i)
	{
		close(utl->fd[utl->m]);
		utl->m++;
	}
	if (handle_builtin(utl->cmds[utl->k], envp, env, root) == 0)
	{
		free_double_array(envp);
		exit(0);
	}
	launch_cmd(utl->cmds[utl->k], envp, NULL, NULL);
	return (0);
}

static int	pre_execution(t_pipeline **utl)
{
	if (!(*utl)->fd)
	{
		ft_putstr_fd("Allocation error\n", 2);
		return (1);
	}
	while ((*utl)->cmds[(*utl)->i] != NULL)
	{
		if (pipe((*utl)->fd + ((*utl)->i * 2)) < 0)
		{
			perror("Pipe");
			return (1);
		}
		(*utl)->i++;
	}
	return (0);
}

int	execute_pipeline(t_pipeline *utl, t_list **env, t_astnode *root)
{
	get_pipe_utils(&utl);
	if (pre_execution(&utl) == 1)
	{
		free_pipeline_util(utl);
		return (1);
	}
	while (utl->k++, utl->cmds[utl->k] != NULL)
	{
		utl->pid = fork();
		if (utl->pid == -1)
		{
			perror("Fork");
			free_pipeline_util(utl);
			return (1);
		}
		else if (utl->pid == 0)
		{
			child_process(utl, env, root);
			restore_std(utl->fds);
		}
		utl->j += 2;
	}
	free_pipeline_util(utl);
	wait_pipes(utl->i);
	return (0);
}
