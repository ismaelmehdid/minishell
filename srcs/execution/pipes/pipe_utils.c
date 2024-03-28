/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:55:34 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/29 00:56:44 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

	util.i = 0;
	util.j = 0;
	util.k = -1;
	util.m = 0;
	while (cmds[util.i] != NULL)
		util.i++;
	util.fd = (int *)malloc(sizeof(int) * (2 * util.i + 1));
	util.i = 0;
	return (util);
}

static int	get_indx(char **envp)
{
	int	i;

	i = -1;
	if (!envp)
		return (-1);
	while (envp[++i] != NULL)
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	return (i);
}

void	launch_cmd(char *cmd, char **envp, char *cmd_path)
{
	char	**cmds;

	if (get_indx(envp) == -1 || envp[get_indx(envp)] == NULL)
	{
		ft_putstr_fd("PATH not set\n", 2);
		return ;
	}
	cmds = split_quotes(cmd, " \t\n\v\f\r", NULL);
	trim_quotes(cmds);
	cmd_path = get_path(cmds[0], envp[get_indx(envp)] + 5);
	if (cmd_path == NULL)
	{
		print_error_not_found(cmds[0]);
		free_double_array(cmds);
		free(cmd_path);
		free(envp);
		exit (127);
	}
	if (execve(cmd_path, cmds, envp) < 0)
	{
		perror("Execve");
		free_double_array(cmds);
		free(envp);
		exit (126);
	}
}

int	get_pipe_size(t_astnode *node)
{
	int			counter;
	t_astnode	*tmp_node;

	counter = 1;
	tmp_node = node;
	while (tmp_node->right && tmp_node->right->type == PIPE_NODE)
	{
		tmp_node = tmp_node->right;
		counter++;
	}
	return (counter);
}