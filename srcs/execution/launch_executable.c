/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:56:59 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/21 01:12:28 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_error(char *cmd)
{
	int	i;

	i = 0;
	ft_putstr_fd("Command not found: ", 2);
	while (cmd[i] && (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13)))
		i++;
	while (cmd[i] && cmd[i] != ' ' && (cmd[i] < 9 || cmd[i] > 13))
	{
		ft_putchar_fd(cmd[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
}

char	*get_path(char *cmd, char *path_full)
{
	int		i;
	char	*cmd_path;
	char	*path;
	char	**paths;

	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (cmd);
	paths = ft_split(path_full, ':');
	i = -1;
	while (paths[++i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (access(cmd_path, F_OK) == 0)
		{
			free_double_array(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_double_array(paths);
	return (NULL);
}

static int	ft_execve(char *cmd_path, char **cmds, char **path_env)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, cmds, path_env) == -1)
		{
			free_double_array(cmds);
			free(cmd_path);
			free_double_array(path_env);
			perror("Execve");
			g_last_command_status = 126;
			return (126);
		}
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

int	launch_executable(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmds;
	int		i;

	i = -1;
	while (envp[++i] != NULL)
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	if (envp[i] == NULL)
	{
		print_error(cmd);
		g_last_command_status = 127;
		return (127);
	}
	cmds = ft_split(cmd, ' ');
	cmd_path = get_path(cmds[0], envp[i] + 5);
	if (cmd_path == NULL)
	{
		not_found(cmds[0]);
		free_double_array(cmds);
		free(cmd_path);
		g_last_command_status = 127;
		return (127);
	}
	return (ft_execve(cmd_path, cmds, envp));
}