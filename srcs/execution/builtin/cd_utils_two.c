/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:56:44 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/11 17:15:41 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_old_pwd(t_list **env, char **old_pwd)
{
	t_list	*current;
	int		i;

	current = *env;
	i = 0;
	*old_pwd = NULL;
	while (current && ft_strncmp("HOME", current->content, 4))
		current = current->next;
	if (current)
	{
		while (current->content[i] && current->content[i] != '=')
			i++;
		if (current->content[i] == '=')
			i++;
	}
	else
	{
		perror("minishell: cd: OLDPWD not set");
		return (1);
	}
	*old_pwd = ft_strdup(current->content + i);
	return (0);
}

static int	update_pwd_to_env(t_list *current, char *cwd)
{
	if (current->content)
		free(current->content);
	current->content = malloc(4 + ft_strlen(cwd) + 1);
	if (!current->content)
	{
		perror("cd");
		return (1);
	}
	current->content[0] = '\0';
	ft_strlcat(current->content, "PWD=", 4 + ft_strlen(cwd) + 1);
	ft_strlcat(current->content, cwd, 4 + ft_strlen(cwd) + 1);
	return (0);
}

static int	add_pwd_to_env(t_list *current, char *cwd)
{
	current = (t_list *)malloc(sizeof(t_list));
	if (!current)
	{
		perror("cd");
		return (1);
	}
	current->content = malloc(4 + ft_strlen(cwd) + 1);
	if (!current->content)
	{
		free(current);
		perror("cd");
		return (1);
	}
	current->content[0] = '\0';
	ft_strlcat(current->content, "PWD=", 4 + ft_strlen(cwd) + 1);
	ft_strlcat(current->content, cwd, 4 + ft_strlen(cwd) + 1);
	current->next = NULL;
	return (0);
}

int	update_pwd(t_list **env)
{
	char	cwd[PATH_MAX];
	t_list	*current;

	current = *env;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (1);
	}
	while (current && ft_strncmp("PWD=", current->content, 4))
		current = current->next;
	if (current && update_pwd_to_env(current, cwd))
		return (1);
	else if (!current && add_pwd_to_env(current, cwd))
		return (1);
	return (0);
}
