/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:56:59 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/26 17:31:59 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes(char *cmd)
{
	int		i;
	int		j;
	char	temp[NAME_MAX];

	i = 0;
	j = 0;
	ft_strlcpy(temp, cmd, ft_strlen(cmd) + 1);
	free(cmd);
	while (temp[i])
	{
		if (temp[i] != '\'' && temp[i] != '"')
			j++;
		i++;
	}
	cmd = malloc(sizeof(char) * j + sizeof(char));
	if (!cmd)
		return ;
	i = 0;
	j = 0;
	while (temp[i])
	{
		if (temp[i] != '\'' && temp[i] != '"')
			cmd[j++] = temp[i];
		i++;
	}
	cmd[j] = '\0';
}

void	print_error_not_found(char *cmd)
{
	int	i;
	int	quote;

	i = 0;
	ft_putstr_fd("Command not found: ", 2);
	while (cmd[i] && is_whitespace(cmd[i]))
		i++;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			quote = cmd[i++];
			while (cmd[i] && cmd[i] != quote)
			{
				ft_putchar_fd(cmd[i], 2);
				i++;
			}
			if (cmd[i] == quote)
				i++;
			continue ;
		}
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

	g_last_command_status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		g_last_command_status = 1;
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, cmds, path_env) == -1)
		{
			g_last_command_status = 126;
			free_double_array(cmds);
			free(cmd_path);
			free_double_array(path_env);
			perror("Execve");
			exit (1);
		}
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
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
		print_error_not_found(cmd);
		g_last_command_status = 127;
		return ;
	}
	cmds = split_quotes(cmd, " \t\n\v\f\r", NULL);
	remove_quotes(cmds[0]);
	cmd_path = get_path(cmds[0], envp[i] + 5);
	if (cmd_path == NULL)
	{
		print_error_not_found(cmds[0]);
		free_double_array(cmds);
		free(cmd_path);
		g_last_command_status = 127;
		return ;
	}
	g_last_command_status = ft_execve(cmd_path, cmds, envp);
}