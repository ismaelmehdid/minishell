/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:56:44 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/05 02:25:03 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	prepare_cd_utils(char **args, char *thepath)
{
	if (size_double_array(args) > 0)
	{
		if (size_double_array(args) > 1)
		{
			ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
			free_double_array(args);
			return (1);
		}
		if (ft_strlen(args[0]) > PATH_MAX)
		{
			ft_putstr_fd("Minishell: cd: ", 2);
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(" : File name too long\n", 2);
			free_double_array(args);
			return (1);
		}
		ft_strlcpy(thepath, args[0], ft_strlen(args[0]) + 1);
	}
	return (0);
}

int	prepare_cd(char *path, char *thepath)
{
	char	**args;

	args = split_quotes(path, " \t\n\v\f\r", NULL);
	if (!args)
		return (126);
	if (trim_quotes(args) != 0)
	{
		free_double_array(args);
		return (126);
	}
	if (prepare_cd_utils(args, thepath) != 0)
		return (1);
	free_double_array(args);
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
