/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:54:18 by asyvash           #+#    #+#             */
/*   Updated: 2024/02/29 00:56:07 by asyvash          ###   ########.fr       */
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

void free_list(t_list **env)
{
    t_list  *temp;

    while ((*env) != NULL)
    {
        temp = (*env);
        (*env) = (*env)->next;
        free(temp->content);
        free(temp);
    }
}

char **create_envp(t_list *env)
{
    char    **envp;
    int     size;
    int     i;

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
        envp[i] = malloc(ft_strlen(env->content) + 1);
        if (envp[i] == NULL)
        {
            free_double_array(envp);
            ft_putstr_fd("Malloc allocation error\n", 2);
            return (NULL);
        }
        envp[i] = ft_strdup(env->content);
        env = env->next;
    }
    return (envp);
}