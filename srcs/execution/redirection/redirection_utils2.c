/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:01:48 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/08 00:37:18 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *get_redirection(char *line)
{
	int i;
	int j;
	int k;
	char *redir;

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

static int count_redirs(t_astnode *node)
{
    int count;

	count = 0;
    while (node->right)
	{
        if (node->left && redir_exist(node->left->value) == 0)
            count++;
        if (node->right && redir_exist(node->right->value) == 0)
            count++;
        node = node->right;
    }
	if (count == 0 && node->value)
	{
        if (redir_exist(node->value) == 0)
            count++;
	}
    return (count);
}

static char **fill_redirs(t_astnode *node, char ***redirs, int i)
{
    while (node->right)
	{
        if (node->left && redir_exist(node->left->value) == 0)
		{
            (*redirs)[++i] = get_redirection(node->left->value);
            if ((*redirs)[i] == NULL)
			{
				ft_putstr_fd("Malloc allocation error\n", 2);
                free_double_array((*redirs));
                return (NULL);
            }
        }
        if (node->right && redir_exist(node->right->value) == 0)
		{
            (*redirs)[++i] = get_redirection(node->right->value);
            if ((*redirs)[i] == NULL)
			{
				ft_putstr_fd("Malloc allocation error\n", 2);
                free_double_array((*redirs));
                return (NULL);
            }
        }
        node = node->right;
    }
    return ((*redirs));
}

char **create_redirs(t_astnode *root)
{
    int size;
	char **redirections;
	
	size = count_redirs(root);
    if (size == 0)
        return (NULL);
	redirections = ft_calloc(size + 1, sizeof(char *));
    if (!redirections)
        return (NULL);
	if (size == 1)
	{
        if (root->value && redir_exist(root->value) == 0)
		{
        	redirections[0] = get_redirection(root->value);
    	    if (redirections[0] == NULL)
			{
				ft_putstr_fd("Malloc allocation error\n", 2);
        		free_double_array(redirections);
        		return (NULL);
    		}
			return(redirections);
        }
	}
    return (fill_redirs(root, &redirections, -1));
}


void del_redirs_from_root(t_astnode **root)
{
	int		i;

    if (*root == NULL)
        return;
	i = 0;
    if (redir_exist((*root)->value) == 0)
	{
		while ((*root)->value[i] != '<' && (*root)->value[i] != '>')
			i++;
		while ((*root)->value[i] == '<' || (*root)->value[i] == '>' \
				|| (*root)->value[i] == ' ')
		{
			(*root)->value[i] = ' ';
			i++;
		}
		while ((*root)->value[i] != ' ' && (*root)->value[i] != '\0')
		{
			(*root)->value[i] = ' ';
			i++;
		}
    }
    del_redirs_from_root(&((*root)->left));
    del_redirs_from_root(&((*root)->right));
}