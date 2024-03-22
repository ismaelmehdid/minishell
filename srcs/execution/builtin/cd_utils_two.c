/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:56:44 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/22 18:10:32 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	prepare_cd(char *path, char *thepath)
{
	char	**args;

	while (*path && (*path == ' ' || (*path>= 9 && *path <= 13)))
		path++;
	args = split_quotes(path, " \t\n\v\f\r");
	if (!args)
		return (126);
	if (size_double_array(args) > 0)
	{
		if (size_double_array(args) > 1)
		{
			ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
			return (1);
		}
		if (ft_strlen(args[0]) > PATH_MAX)
		{
			ft_putstr_fd("Minishell: cd: ", 2);
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(" : File name too long\n", 2);
			return (1);
		}
		ft_strlcpy(thepath, args[0], ft_strlen(args[0]) + 1);
	}
	free_double_array(args);
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

static int	add_pwd_to_env(t_list **env, char *cwd)
{
	t_list	*current;

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
	current->next = *env;
	*env = current;
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
	else if (!current && add_pwd_to_env(env, cwd))
		return (1);
	return (0);
}
