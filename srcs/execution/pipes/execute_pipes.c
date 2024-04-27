/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/27 15:41:27 by imehdid          ###   ########.fr       */
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
	stop_exec(utl);
}

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
	if (WIFEXITED(status))
		g_last_command_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status) && g_last_command_status != 131)
		g_last_command_status = WTERMSIG(status) + 128;
}

static void	child_process(t_pipeline *utl, t_list **env, t_astnode *root)
{
	char	**envp;

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
	if (handle_builtin(utl->cmds[utl->k], env, root, utl->fds) == 0)
	{
		free_child_if_builtin(utl, env, root);
		exit(0);
	}
	envp = create_envp(*env);
	close(utl->fds[0]);
	close(utl->fds[1]);
	launch_cmd(utl->cmds[utl->k], envp, NULL, NULL);
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
