/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:04:15 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/14 22:20:28 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	if (redir_exist((*root)->value) == 0)
		del_redirs_from_root(&((*root)));
    del_redirs_from_root(&((*root)->left));
    del_redirs_from_root(&((*root)->right));
}

static int count_in_node(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '>' || line[i] == '<')
		{
			count++;
			while (line[i] == '>' || line[i] == '<')
				i++;
		}
		i++;
	}
	return (count);
}

int count_redirs(t_astnode *node)
{
    int count;

	count = 0;
    while (node->right)
	{
        if (node->left && redir_exist(node->left->value) == 0)
            count += count_in_node(node->left->value);
        if (node->right && redir_exist(node->right->value) == 0)
            count += count_in_node(node->right->value);;
        node = node->right;
    }
	if (count == 0 && node->value)
	{
        if (redir_exist(node->value) == 0)
            count += count_in_node(node->value);
	}
    return (count);
}

int still_exist(char *line)
{
	static int i;

	if (!i)
		i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '>' || line[i] == '<')
		{
			while (line[i] == '>' || line[i] == '<')
				i++;
			break ;
		}
		i++;
	}
	while (line[i] != '\0')
	{
		if (line[i] == '>' || line[i] == '<')
		{
			return (i);
			break ;
		}
		i++;
	}
	if (line[i] == '\0')
		i = 0;
	return (-1);
}

char    *ft_strjoin_free(char *s1, char const *s2, int s2_len)
{
    int			i;
    int			j;
    char		*res;

    i = 0;
    j = ft_strlen(s1);
    res = malloc(j + s2_len + 1);
    if (!res)
    {
        free(s1);
        return (NULL);
    }
    j = 0;
    while (s1[i])
    {
        res[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        res[i + j] = s2[j];
        j++;
    }
    res[i + j] = '\0';
    free(s1);
    return (res);
}