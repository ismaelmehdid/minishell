/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/29 22:31:47 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	parent_procces(t_pipeline *utl)
{
	int	i;
	int	status;

	i = 0;
	while (i < utl->j)
	{
		close(utl->fd[i]);
		i++;
	}
	waitpid(utl->pid, &status, 0);
	if (WIFEXITED(status) != 0 && g_last_command_status != 130)
		g_last_command_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status) && g_last_command_status != 131)
		g_last_command_status = WTERMSIG(status) + 128;
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
	(*utl)->fds[0] = dup(STDIN_FILENO);
	(*utl)->fds[1] = dup(STDOUT_FILENO);
	if ((*utl)->fds[0] < 0 || (*utl)->fds[1] < 0)
		return (1);
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
			free_pipeline_util(utl);
			return (1);
		}
		else if (utl->pid == 0)
			child_process(utl, env, root);
		else
			parent_procces(utl);
		utl->j += 2;
	}
	restore_std(utl->fds);
	free_pipeline_util(utl);
	return (0);
}

int	pipeline(t_pipeline *utl, t_list **env, t_astnode *root)
{
	if (execute_pipeline(utl, env, root) == 1)
	{
		free_double_array(utl->cmds);
		return (1);
	}
	free_double_array(utl->cmds);
	return (0);
}
