/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:54:18 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/01 23:22:22 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	free_list(t_list **env)
{
	t_list	*temp;

	while ((*env) != NULL)
	{
		temp = (*env);
		(*env) = (*env)->next;
		free(temp->content);
		free(temp);
	}
}

char	**create_envp(t_list *env)
{
	char	**envp;
	int		size;
	int		i;

	size = ft_lstsize(env);
	envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!envp)
	{
		ft_putstr_fd("Malloc allocation error\n", 2);
		return (NULL);
	}
	i = -1;
	while (i++, i < size)
	{
		envp[i] = ft_strdup(env->content);
		if (envp[i] == NULL)
		{
			free_double_array(envp);
			ft_putstr_fd("Malloc allocation error\n", 2);
			return (NULL);
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	create_env(t_list **env, char **envp)
{
	t_list	*new_node;
	int		i;

	i = 0;
	*env = NULL;
	while (envp[i] != NULL)
	{
		new_node = (t_list *)malloc(sizeof(t_list));
		if (new_node == NULL)
		{
			ft_putstr_fd("Allocation error\n", 2);
			return (1);
		}
		new_node->content = ft_strdup(envp[i]);
		if (new_node->content == NULL)
		{
			ft_putstr_fd("Allocation error\n", 2);
			return (1);
		}
		new_node->next = *env;
		*env = new_node;
		i++;
	}
	return (0);
}
