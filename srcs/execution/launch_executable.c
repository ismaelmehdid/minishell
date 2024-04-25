/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:56:59 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/25 17:53:32 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error_not_found(char *cmd, int code)
{
	if (code == 1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (code == 2)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Command not found\n", 2);
	}
}

static void	wait_pids(int status, pid_t pid)
{
	waitpid(pid, &status, 0);
	g_last_command_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status) && g_last_command_status != 131)
		g_last_command_status = WTERMSIG(status) + 128;
}

static void	ft_execve(
	char *cmd_path,
	char **cmds,
	char **path_env,
	int status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		free_double_array(cmds);
		free(cmd_path);
		g_last_command_status = 1;
		return ;
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, cmds, path_env) == -1)
		{
			print_error_not_found(cmds[0], 2);
			exit (126);
		}
	}
	else
		wait_pids(status, pid);
	free_double_array(cmds);
	free(cmd_path);
}

void	launch_executable(char *cmd, char **envp, int i)
{
	char	*cmd_path;
	char	**cmds;

	while (envp[++i] != NULL)
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	cmds = split_quotes(cmd, " \t\n\v\f\r", NULL);
	trim_quotes(cmds);
	if (!envp[i] && cmds && access(cmds[0], F_OK) != 0)
	{
		print_error_not_found(cmd, 1);
		free_double_array(cmds);
		g_last_command_status = 127;
		return ;
	}
	cmd_path = get_path(cmds[0], envp[i] + 5);
	if (cmd_path == NULL)
	{
		print_error_not_found(cmds[0], 2);
		free_double_array(cmds);
		g_last_command_status = 127;
		return ;
	}
	ft_execve(cmd_path, cmds, envp, 0);
}
