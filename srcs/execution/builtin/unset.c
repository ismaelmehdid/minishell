/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:54 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/19 00:12:09 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int  invalid_parameter(char *param)
{
    int i;

    i = 0;
    while (param[i] != '\0')
    {
        if (param[i] == '=')
        {
            ft_putstr_fd("unset: ", 2);
            ft_putstr_fd(param, 2);
            ft_putstr_fd(": invalid parameter name\n", 2);
            return (-1);
        }
        i++;
    }
    return (0);
}

static char **create_key(char *key)
{
	char	**new_key;
	char	**temp;
	char	*old_str;

	temp = NULL;
	old_str = NULL;
	if (invalid_parameter(key) == 1)
		return (NULL);
	new_key = ft_split(key, ' ');
	if (!new_key)
	{
		ft_putstr_fd("Malloc allocation error\n", 2);
		return (NULL);
	}
	temp = new_key;
	while (*temp)
	{
		old_str = *temp;
		*temp = ft_strjoin(old_str, "=");
		if (!*temp)
		{
			ft_putstr_fd("Malloc allocation error\n", 2);
			free_double_array(new_key);
			return (NULL);
		}
		free(old_str);
		temp++;
	}
	*temp = NULL;
	return (new_key);
}

static void	search_and_remove_env(t_list **head, char **args)
{
	t_list	*current;
	t_list	*previous;

	current = *head;
	previous = NULL;
	while (*args)
	{
		while (current &&
			ft_strncmp(current->content, *args, ft_strlen(*args)) != 0)
		{
			previous = current;
			current = current->next;
		}
		if (current)
		{
			if (!previous)
				(*head) = current->next;
			else
				previous->next = current->next;
			free(current->content);
			free(current);
		}
		previous = NULL;
		current = *head;
		args++;
	}
}

int  execute_unset(t_list **head, char *key)
{
	char	**args;

	if (key[0] == '\0')
		return (0);
	args = create_key(key);
	if (!args)
		return (2);
	search_and_remove_env(head, args);
	free_double_array(args);
	return (0);
}