/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:01:48 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/21 00:45:28 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_index_after_quotes(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] == quote)
				i++;
			continue ;
		}
		if (line[i] == '>' || line[i] == '<')
			return (i);
		i++;
	}
	return (0);
}

char	*get_redir(char *line)
{
	int			i;
	int			j;
	int			k;
	char		*redir;

	i = get_index_after_quotes(line);
	j = i;
	while (line[j] == '>' || line[j] == '<' || is_whitespace(line[j]))
		j++;
	while (!is_whitespace(line[j]) && line[j] != '\0')
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

static char	**fill_list(char *content, char ***redirs, int i, int j)
{
	if (content && redir_exist(content) == 0)
	{
		(*redirs)[++i] = get_redir(content);
		if ((*redirs)[i] == NULL)
		{
			ft_putstr_fd("Allocation error\n", 2);
			free_double_array((*redirs));
			return (NULL);
		}
		while (1)
		{
			j = still_exist(content);
			if (j == -1)
				break ;
			(*redirs)[++i] = get_redir(content + j);
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

char	**create_list(t_astnode *root)
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
	return (fill_list(root->value, &redirs, -1, 0));
}
