/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:23:27 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/27 17:02:56 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	read_current_dir(char *filename)
{
	DIR					*dir;
	struct dirent		*entry;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir error\n");
		return (1);
	}
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (ft_strncmp(filename, entry->d_name,
				ft_strlen(filename)) == 0)
			return (0);
	}
	closedir(dir);
	return (1);
}

static int	check_file_cmd(char *cmd, int i)
{
	if (cmd[0] && cmd[1] && cmd[0] == '.' && \
		cmd[1] == '/')
		i += 2;
	else
	{
		if (read_current_dir(cmd) == 0)
		{
			print_error_not_found(cmd, 2);
			return (1);
		}
		else
			return (0);
	}
	if (cmd[i] == '\0' || is_whitespace(cmd[i]))
	{
		ft_putstr_fd("minishell: ./: Is a directory\n", 2);
		g_last_command_status = 126;
		return (1);
	}
	if (read_current_dir(cmd + i) == 0)
		return (0);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

static char	*extract_path(char **paths, char *cmd_path, char *cmd, int i)
{
	char	*path;

	while (paths[++i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
		{
			ft_putstr_fd("Allocation error\n", 2);
			return (NULL);
		}
		cmd_path = ft_strjoin(path, cmd);
		if (!cmd_path)
		{
			ft_putstr_fd("Allocation error\n", 2);
			return (NULL);
		}
		free(path);
		if (access(cmd_path, F_OK) == 0)
		{
			free_double_array(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	return (NULL);
}

char	*get_path(char *cmd, char *path_full)
{
	char	*cmd_path;
	char	**paths;

	if (check_file_cmd(cmd, 0) == 1)
		return (NULL);
	if (!cmd || ft_strlen(cmd) == 0)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	paths = ft_split(path_full, ':');
	cmd_path = extract_path(paths, NULL, cmd, -1);
	if (cmd_path != NULL)
		return (cmd_path);
	free_double_array(paths);
	if (g_last_command_status != 126)
		print_error_not_found(cmd, 2);
	return (NULL);
}
