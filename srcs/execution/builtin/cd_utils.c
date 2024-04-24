/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <imehdid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:15:42 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/24 13:17:54 by imehdid          ###   ########.fr       */
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
	current->export_marked = true;
	current->value_assigned = true;
	current->export_marked_sub = true;
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

int	get_old_pwd(t_list **env, char **old_pwd)
{
	t_list	*current;
	int		i;

	current = *env;
	i = 0;
	*old_pwd = NULL;
	while (current && ft_strncmp("OLDPWD", current->content, 6))
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
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	*old_pwd = ft_strdup(current->content + i);
	return (0);
}
