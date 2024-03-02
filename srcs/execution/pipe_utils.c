/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:55:34 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/01 20:54:55 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void not_found(char *cmd)
{
	ft_putstr_fd("Command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	write(2, "\n", 1);
}

void	close_pipe_fds(int *fd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(fd[i]);
		i++;
	}
}

t_pipeline	get_pipe_utils(char **cmds)
{
	t_pipeline	util;

	util.path = getenv("PATH");
	util.path_env = (char *[]){NULL, NULL};
	util.path_env[0] = ft_strjoin("PATH=", util.path);
	util.i = 0;
	util.j = 0;
	util.k = -1;
	while (cmds[util.i] != NULL)
		util.i++;
	util.fd = (int *)malloc(sizeof(int) * (2 * util.i + 1));
	util.i = 0;
	return (util);
}

void	launch_cmd(char *cmd, char *path, char **path_env)
{
	char	**cmds;
	char	*cmd_path;

	cmds = ft_split(cmd, ' ');
	cmd_path = get_path(cmds[0], path);
	if (cmd_path == NULL)
	{
		not_found(cmds[0]);
		free_double_array(cmds);
		free(cmd_path);
		exit (127);
	}
	if (execve(cmd_path, cmds, path_env) < 0)
	{
		perror("execve");
		free(cmd_path);
		free_double_array(cmds);
		exit (128);
	}
}