/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:15:42 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/06 21:32:17 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	update_old_pwd_to_env(t_list *current, char *cwd)
{
	if (current->content)
		free(current->content);
	current->content = malloc(7 + ft_strlen(cwd) + 1); // 7 value is corresponding to the size of : "OLDPWD="
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

static int	add_old_pwd_to_env(t_list *current, char *cwd)
{
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
	current->next = NULL;
	return (0);
}

int	update_old_pwd_dir(t_list **env)
{
	char	cwd[PATH_MAX];
	t_list	*current;

	current = *env;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd");
		return (1);
	}
	while (current && ft_strncmp("OLDPWD=", current->content, 7))
		current = current->next;
	if (current && update_old_pwd_to_env(current, cwd))
		return (1);
	else if (!current && add_old_pwd_to_env(current, cwd))
		return (1);
	return (0);
}
