/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:47:46 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/29 21:47:01 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	finish_init_pipe(
	t_astnode *root,
	int counter,
	t_pipeline *utl,
	t_list **env)
{
	if (root->left && root->right && root->right->type == COMMAND_NODE)
	{
		utl->cmds[counter] = ft_strdup(root->left->value);
		utl->cmds[counter + 1] = ft_strdup(root->right->value);
		if (utl->cmds[counter] == NULL || utl->cmds[counter + 1] == NULL)
		{
			free_double_array(utl->cmds);
			return (1);
		}
	}
	if (execute_pipeline(utl, env) == 1)
	{
		free_double_array(utl->cmds);
		return (1);
	}
	free_double_array(utl->cmds);
	return (0);
}

void	fill_redirs(t_pipeline *utl, char *content, int i, int j)
{
	int	k;

	k = 0;
	while (content[j])
	{
		while (content[j] && content[j] != '<' && content[j] != '>')
			j++;
		while (content[j] == '<' || content[j] == '>')
		{
			utl->redirs[i][k] = content[j];
			j++;
			k++;
		}
		while (is_whitespace(content[j]))
			j++;
		while (content[j] && !is_whitespace(content[j]))
		{
			utl->redirs[i][k] = content[j];
			j++;
			k++;
		}
		utl->redirs[i][k++] = '\t';
	}
	utl->redirs[i][k] = '\0';
}

int	exctract_redirs(t_pipeline *utl, t_astnode *root, int i, char *content)
{
	t_astnode	*tmp;

	tmp = root;
	utl->redirs = ft_calloc(get_pipe_size(root) + 2, sizeof(char *));
	if (utl->redirs == NULL)
		return (1);
	while (tmp)
	{
		content = get_content(tmp);
		if (!content)
			return (1);
		utl->redirs[i] = ft_calloc((ft_strlen(content) + 1), sizeof(char));
		if (!utl->redirs[i])
		{
			free(content);
			return (1);
		}
		fill_redirs(utl, content, i, 0);
		free(content);
		tmp = tmp->right;
		i++;
	}
	del_redirs_from_root(&root);
	return (0);
}

static int	pre_init_pipe(t_pipeline *utl, t_astnode *root)
{
	if (exctract_redirs(utl, root, 0, NULL) == 1)
	{
		free_double_array(utl->redirs);
		return (1);
	}
	utl->cmds = ft_calloc(get_pipe_size(root) + 2, sizeof(char *));
	if (utl->cmds == NULL)
	{
		free_double_array(utl->redirs);
		return (1);
	}
	return (0);
}

int	init_pipe(t_astnode *orig, t_list **env, int counter)
{
	t_pipeline	utl;
	t_astnode	*root;

	root = orig;
	if (pre_init_pipe(&utl, root) == 1)
		return (1);
	while (root->right && root->right->type != COMMAND_NODE)
	{
		utl.cmds[counter] = ft_strdup(root->left->value);
		if (utl.cmds[counter] == NULL)
		{
			free_double_array(utl.cmds);
			free_double_array(utl.redirs);
			return (1);
		}
		root = root->right;
		counter++;
	}
	if (finish_init_pipe(root, counter, &utl, env) == 1)
		return (1);
	return (0);
}
