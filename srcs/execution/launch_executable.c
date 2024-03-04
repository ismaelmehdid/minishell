/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:56:59 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/04 22:14:00 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path(char *cmd, char *path_full)
{
	int		i;
	char	*cmd_path;
	char	*path;
	char	**paths;

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

static void	ft_execve(char *cmd_path, char **cmds, char **path_env)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		return ;
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, cmds, path_env) == -1)
		{
			free_double_array(cmds);
			free(cmd_path);
			free_double_array(path_env);
			perror("Execve");
		}
	}
	else
		waitpid(pid, NULL, 0);
}

void	launch_executable(char *cmd, char **envp)
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
		ft_putstr_fd("PATH not set\n", 2);
		return ;
	}
	cmds = ft_split(cmd, ' ');
	cmd_path = get_path(cmds[0], envp[i] + 5);
	if (cmd_path == NULL)
	{
		not_found(cmds[0]);
		free_double_array(cmds);
		free(cmd_path);
		return ;
	}
	ft_execve(cmd_path, cmds, envp);
}