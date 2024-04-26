/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:54:18 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/26 23:49:53 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_envp_loop(t_list *env, char **envp)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->export_marked == true && env->value_assigned == true)
		{
			envp[i] = ft_strdup(env->content);
			if (envp[i] == NULL)
			{
				free_double_array(envp);
				ft_putstr_fd("Malloc allocation error\n", 2);
				return ;
			}
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
}

char	**create_envp(t_list *env)
{
	char	**envp;
	int		size;

	size = ft_lstsize(env, true);
	envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!envp)
	{
		ft_putstr_fd("Allocation error\n", 2);
		return (NULL);
	}
	create_envp_loop(env, envp);
	if (!envp)
		return (NULL);
	return (envp);
}

static void	set_env_utils(t_list **new_node, char **envp, int i)
{
	(*new_node)->content = ft_strdup(envp[i]);
	(*new_node)->export_marked = true;
	(*new_node)->value_assigned = true;
	(*new_node)->export_marked_sub = true;
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
		set_env_utils(&new_node, envp, i);
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
