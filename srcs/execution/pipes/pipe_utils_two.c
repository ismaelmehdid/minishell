/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:56:57 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/22 13:51:43 by asyvash          ###   ########.fr       */
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

void	get_pipe_utils(t_pipeline **utl)
{
	(*utl)->i = 0;
	(*utl)->j = 0;
	(*utl)->k = -1;
	(*utl)->m = 0;
	while ((*utl)->cmds[(*utl)->i] != NULL)
		(*utl)->i++;
	(*utl)->fd = (int *)malloc(sizeof(int) * (2 * (*utl)->i + 1));
	(*utl)->i = 0;
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
