/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/01 20:42:06 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	wait_pipes(int num_processes)
{
	int	i;

	i = 0;
	while (i < num_processes)
	{
		wait(NULL);
		i++;
	}
}

static int	pipe_child(char **cmds, t_pipeline *utl)
{
	if (cmds[utl->k + 1] != NULL)
	{
		if (dup2(utl->fd[utl->j + 1], 1) < 0)
		{
			perror("dup2");
			return (1);
		}
	}
	if (utl->j != 0)
	{
		if (dup2(utl->fd[utl->j - 2], 0) < 0)
		{
			perror("dup2");
			return (1);
		}
	}
	utl->m = 0;
	while (utl->m < 2 * utl->i)
	{
		close(utl->fd[utl->m]);
		utl->m++;
	}
	launch_cmd(cmds[utl->k], utl->path, utl->path_env);
	return (0);
}

static int	pre_execution(char **cmds, t_pipeline *utl)
{
	if (!utl->fd)
	{
		printf("\nMalloc error\n");
		return (1);
	}
	if (utl->path == NULL)
	{
		printf("PATH variable not set");
		return (1);
	}
	while (cmds[utl->i] != NULL)
	{
		if (pipe(utl->fd + (utl->i * 2)) < 0)
		{
			perror("couldn't pipe");
			return (1);
		}
		utl->i++;
	}
	return (0);
}

int	execute_pipeline(char **cmds)
{
	t_pipeline	utl;

	utl = get_pipe_utils(cmds);
	if (pre_execution(cmds, &utl) == 1)
		return (1);
	while (utl.k++, cmds[utl.k] != NULL)
	{
		if ((utl.pid = fork()) == -1)
		{
			perror("fork");
			return (1);
		}
		else if (utl.pid == 0)
			pipe_child(cmds, &utl);
		else if (utl.pid < 0)
		{
			perror("error");
			return (1);
		}
		utl.j += 2;
	}
	close_pipe_fds(utl.fd, 2 * utl.i);
	wait_pipes(utl.i);
	return (0);
}