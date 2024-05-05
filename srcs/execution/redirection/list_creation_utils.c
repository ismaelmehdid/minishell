/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <imehdid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:04:15 by asyvash           #+#    #+#             */
/*   Updated: 2024/05/05 13:17:10 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	del_redirs_from_root(t_astnode **root)
{
	int	i;

	if (*root == NULL)
		return ;
	if (redir_exist((*root)->value) == 0)
	{
		i = get_index_after_quotes((*root)->value);
		while ((*root)->value[i] != '<' && (*root)->value[i] != '>')
			i++;
		while ((*root)->value[i] == '<' || (*root)->value[i] == '>' \
				|| is_whitespace((*root)->value[i]))
		{
			(*root)->value[i] = ' ';
			i++;
		}
		while (!is_whitespace((*root)->value[i]) && (*root)->value[i] != '\0')
			(*root)->value[i++] = ' ';
	}
	if (redir_exist((*root)->value) == 0)
		del_redirs_from_root(&((*root)));
	del_redirs_from_root(&((*root)->left));
	del_redirs_from_root(&((*root)->right));
}

static int	count_in_node(char *line)
{
	int	i;
	int	count;

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

int	count_redirs(t_astnode *root)
{
	int	count;

	count = 0;
	if (root->value)
	{
		if (redir_exist(root->value) == 0)
			count += count_in_node(root->value);
	}
	return (count);
}

int	still_exist(char *line)
{
	static int	i;

	if (!i)
		i = get_index_after_quotes(line);
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
			return (i);
		i++;
	}
	if (line[i] == '\0')
		i = 0;
	return (-1);
}

char	*ft_strjoin_free(char *s1, char const *s2, int s2_len)
{
	int			i;
	int			j;
	char		*res;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = ft_strlen(s1);
	res = malloc(j + s2_len + 1);
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	j = 0;
	while (s1[++i])
		res[i] = s1[i];
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return (res);
}
