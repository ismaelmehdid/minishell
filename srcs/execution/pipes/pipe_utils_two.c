/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:56:57 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/15 12:57:30 by imehdid          ###   ########.fr       */
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
	free(fd);
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
