/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:27 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/06 21:32:15 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_old_pwd(t_list **env)
{
	t_list	*current;
	int		i;

	current = *env;
	i = 0;
	while (current && ft_strncmp("OLDPWD", current->content, 6))
		current = current->next;
	if (current)
	{
		while (current->content[i] && current->content[i] != '=')
			i++;
		if (current->content[i] == '=')
			return (current->content + i + 1);
	}
	return (NULL);
}

static int	change_to_absolute_path_dir(char *path, t_list **env)
{
	if (update_old_pwd_dir(env))
		return (1);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static int	change_to_relative_path_dir(char *path, t_list **env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (1);
	}
	if (ft_strlen(cwd) + ft_strlen(path) + 1 > PATH_MAX)
		return (1);
	ft_strlcat(cwd, "/", sizeof(cwd));
	ft_strlcat(cwd, path, sizeof(cwd));
	if (update_old_pwd_dir(env))
		return (1);
	if (chdir(cwd) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static int	change_to_old_pwd_dir(t_list **env)
{
	char	*old_pwd;

	old_pwd = get_old_pwd(env);
	if (!old_pwd)
	{
		perror("minishell: cd: OLDPWD not set");
		return (127);
	}
	if (update_old_pwd_dir(env))
		return (1);
	if (chdir(old_pwd) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	execute_cd(char *path, t_list **env)
{
	while (*path && (*path == ' ' || (*path >= 9 && *path <= 13)))
		path++;
	if (path[0] == '/')
		return (change_to_absolute_path_dir(path, env));
	else if (path[0] == '-')
		return (change_to_old_pwd_dir(env));
	else
		return (change_to_relative_path_dir(path, env));
	return (127);
}
