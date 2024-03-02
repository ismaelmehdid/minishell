/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:54 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/02 20:50:36 by imehdid          ###   ########.fr       */
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

static char *create_key(char *key)
{
    int     i;
    char    *new_key;
    
    i = 0;
    if (invalid_parameter(key) == 1)
        return (NULL);
    while (key[i] == ' ')
        i++;
    new_key = malloc(ft_strlen(key) + 2);
    if (!new_key)
    {
        ft_putstr_fd("Malloc allocation error\n", 2);
        return (NULL);
    }
    new_key = ft_strjoin(key + i, "=");
	return (new_key);
}

int  execute_unset(t_list **head, char *key)
{
    char    *arg;
    t_list *prev;
    t_list *cur;

	if (key[0] == '\0')
		return (0);
    arg = create_key(key);
    if (!arg)
        return (2);
    prev = NULL;
    cur = *head;
    while (cur != NULL && ft_strncmp(cur->content, arg, ft_strlen(arg)) != 0)
	{
        prev = cur;
        cur = cur->next;
    }
    free(arg);
    if (cur == NULL)
		return (2);
    if (prev == NULL)
        (*head) = cur->next;
	else
        prev->next = cur->next;
    free(cur);
    return (0);
}