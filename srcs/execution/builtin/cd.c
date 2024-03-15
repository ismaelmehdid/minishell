/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:27 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/15 22:39:24 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	change_to_home_dir(t_list **env)
{
	char	cwd[PATH_MAX];
	char	*home;

	home = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (126);
	}
	if (get_home_dir(&home, env))
		return (1);
	if (chdir(home) != 0)
	{
		free(home);
		perror("cd");
		return (1);
	}
	free(home);
	if (update_old_pwd_dir(env, cwd))
		return (126);
	if (update_pwd(env))
		return (126);
	return (0);
}

static int	change_to_absolute_path_dir(char *path, t_list **env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (126);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	if (update_old_pwd_dir(env, cwd))
		return (126);
	if (update_pwd(env))
		return (126);
	return (0);
}

static int	change_to_relative_path_dir(char *path, t_list **env)
{
	char	cwd[PATH_MAX];
	char	actual_cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (126);
	}
	ft_strlcpy(actual_cwd, cwd, sizeof(cwd));
	if (ft_strlen(cwd) + ft_strlen(path) + 1 > PATH_MAX)
		return (1);
	ft_strlcat(cwd, "/", sizeof(cwd));
	ft_strlcat(cwd, path, sizeof(cwd));
	if (chdir(cwd) != 0)
	{
		perror("cd");
		return (1);
	}
	if (update_old_pwd_dir(env, actual_cwd))
		return (126);
	if (update_pwd(env))
		return (126);
	return (0);
}

static int	change_to_old_pwd_dir(t_list **env)
{
	char	*old_pwd;
	char	cwd[PATH_MAX];

	old_pwd = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (126);
	}
	if (get_old_pwd(env, &old_pwd))
		return (1);
	if (chdir(old_pwd) != 0)
	{
		free(old_pwd);
		perror("cd");
		return (1);
	}
	free(old_pwd);
	if (update_old_pwd_dir(env, cwd))
		return (126);
	if (update_pwd(env))
		return (126);
	return (0);
}

int	execute_cd(char *path, t_list **env)
{
	while (*path && (*path == ' ' || (*path >= 9 && *path <= 13)))
		path++;
	if (path[0] == '\0')
		return (change_to_home_dir(env));
	if (path[0] == '/')
		return (change_to_absolute_path_dir(path, env));
	else if (path[0] == '-')
		return (change_to_old_pwd_dir(env));
	else
		return (change_to_relative_path_dir(path, env));
	return (1);
}
