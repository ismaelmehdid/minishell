/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 01:17:06 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/28 19:04:38 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_fds_dup(char **cmds, t_pipeline *utl)
{
	if (cmds[utl->k + 1] != NULL)
	{
		if (dup2(utl->fd[utl->j + 1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			return (1);
		}
	}
	if (utl->j != 0)
	{
		if (dup2(utl->fd[utl->j - 2], STDIN_FILENO) < 0)
		{
			perror("dup2");
			return (1);
		}
	}
	return (0);
}

void	free_pipeline_util(t_pipeline *utl)
{
	if (utl->redirs)
		free_double_array(utl->redirs);
	if (utl->fd)
		close_pipe_fds(utl->fd, utl->i * 2);
	if (utl->fds[0] >= 0)
		close(utl->fds[0]);
	if (utl->fds[1] >= 0)
		close(utl->fds[1]);
}

void	stop_exec(t_pipeline *utl, t_list **env, t_astnode *root)
{
	if (g_last_command_status == 130)
	{
		free_child_if_builtin(utl, env, root);
		exit (130);
	}
	else if (g_last_command_status == 3)
	{
		free_child_if_builtin(utl, env, root);
		exit (0);
	}
	else if (g_last_command_status == 350)
	{
		free_child_if_builtin(utl, env, root);
		exit (1);
	}
	else if (g_last_command_status == 1)
	{
		free_child_if_builtin(utl, env, root);
		exit (1);
	}
}

int	check_empty_status(char *cmds)
{
	int	i;

	i = 0;
	while (is_whitespace(cmds[i]))
		i++;
	if (cmds[i] == '\0')
		return (0);
	return (1);
}
