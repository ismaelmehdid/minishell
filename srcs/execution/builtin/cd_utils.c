/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:15:42 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/26 19:21:01 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	update_old_pwd_to_env(t_list *current, char *cwd)
{
	if (current->content)
		free(current->content);
	current->content = malloc(7 + ft_strlen(cwd) + 1);
	if (!current->content)
	{
		perror("cd");
		return (1);
	}
	current->content[0] = '\0';
	ft_strlcat(current->content, "OLDPWD=", 7 + ft_strlen(cwd) + 1);
	ft_strlcat(current->content, cwd, 7 + ft_strlen(cwd) + 1);
	return (0);
}

static int	add_old_pwd_to_env(t_list **env, char *cwd)
{
	t_list	*current;

	current = (t_list *)malloc(sizeof(t_list));
	if (!current)
	{
		perror("cd");
		return (1);
	}
	current->content = malloc(7 + ft_strlen(cwd) + 1);
	if (!current->content)
	{
		free(current);
		perror("cd");
		return (1);
	}
	current->content[0] = '\0';
	ft_strlcat(current->content, "OLDPWD=", 7 + ft_strlen(cwd) + 1);
	ft_strlcat(current->content, cwd, 7 + ft_strlen(cwd) + 1);
	current->next = *env;
	*env = current;
	return (0);
}

int	update_old_pwd_dir(t_list **env, char *cwd)
{
	t_list	*current;

	current = *env;
	while (current && ft_strncmp("OLDPWD=", current->content, 7))
		current = current->next;
	if (current && update_old_pwd_to_env(current, cwd))
		return (1);
	else if (!current && add_old_pwd_to_env(env, cwd))
		return (1);
	return (0);
}

int	get_home_dir(char **home, t_list **env)
{
	t_list	*current;
	int		i;

	current = *env;
	i = 0;
	*home = NULL;
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
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (current->content[i] == '\0')
		*home = ft_strdup(".");
	else
		*home = ft_strdup(current->content + i);
	return (0);
}
