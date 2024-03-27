/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:01:48 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/26 23:12:45 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_redir(char *line)
{
	int		i;
	int		j;
	int		k;
	char	*redir;

	i = 0;
	while (line[i] != '<' && line[i] != '>')
		i++;
	j = i;
	while (line[j] == '>' || line[j] == '<' || line[j] == ' ')
		j++;
	while (line[j] != ' ' && line[j] != '\0')
		j++;
	k = 0;
	redir = ft_calloc(j - i + 1, sizeof(char));
	if (!redir)
		return (NULL);
	while (i < j)
	{
		redir[k] = line[i];
		i++;
		k++;
	}
	return (redir);
}

static char	**fill_last_redir(t_astnode *node, char ***redirs, int i, int j)
{
	if (node->value && redir_exist(node->value) == 0)
	{
		(*redirs)[++i] = get_redir(node->value);
		if ((*redirs)[i] == NULL)
		{
			ft_putstr_fd("Malloc allocation error\n", 2);
			free_double_array((*redirs));
			return (NULL);
		}
		while (1)
		{
			j = still_exist(node->value);
			if (j == -1)
				break ;
			(*redirs)[++i] = get_redir(node->value + j);
			if ((*redirs)[i] == NULL)
			{
				ft_putstr_fd("Malloc allocation error\n", 2);
				free_double_array((*redirs));
				return (NULL);
			}
		}
	}
	return (*(redirs));
}

static char	**fill_redirs(t_astnode *node, char ***redirs, int i, int j)
{
	while (node->right)
	{
		if (node->left && redir_exist(node->left->value) == 0)
		{
			(*redirs)[++i] = get_redir(node->left->value);
			while (1)
			{
				j = still_exist(node->left->value);
				if (j == -1)
					break ;
				(*redirs)[++i] = get_redir(node->left->value + j);
				if ((*redirs)[i] == NULL || (*redirs)[i - 1] == NULL)
				{
					ft_putstr_fd("Malloc allocation error\n", 2);
					free_double_array((*redirs));
					return (NULL);
				}
			}
		}
		if (node->right == NULL)
			break ;
		node = node->right;
	}
	return (fill_last_redir(node, redirs, i, 0));
}

static char	**fill_root_simple(t_astnode *root, char ***redirs, int i, int j)
{
	if (root->value && redir_exist(root->value) == 0)
	{
		(*redirs)[++i] = get_redir(root->value);
		if ((*redirs)[i] == NULL)
		{
			ft_putstr_fd("Allocation error\n", 2);
			free_double_array((*redirs));
			return (NULL);
		}
		while (1)
		{
			j = still_exist(root->value);
			if (j == -1)
				break ;
			(*redirs)[++i] = get_redir(root->value + j);
			if ((*redirs)[i] == NULL)
			{
				ft_putstr_fd("Allocation error\n", 2);
				free_double_array((*redirs));
				return (NULL);
			}
		}
	}
	return ((*redirs));
}

char	**create_redirs(t_astnode *root)
{
	int		size;
	char	**redirs;

	size = count_redirs(root);
	if (size == 0)
		return (NULL);
	redirs = ft_calloc(size + 2, sizeof(char *));
	if (!redirs)
	{
		ft_putstr_fd("Allocation error\n", 2);
		g_last_command_status = 350;
		return (NULL);
	}
	if (!root->left && !root->right)
		return (fill_root_simple(root, &redirs, -1, 0));
	return (fill_redirs(root, &redirs, -1, 0));
}
