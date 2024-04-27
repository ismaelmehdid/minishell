/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:54 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/27 17:01:14 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	cmp_var_name(char *existing, char *to_remove)
{
	int	i;

	i = 0;
	while (to_remove[i] && existing[i] && existing[i] != '=')
	{
		if (to_remove[i] != existing[i])
			return (0);
		i++;
	}
	if (to_remove[i] == '\0' && (existing[i] == '\0' || existing[i] == '='))
		return (1);
	return (0);
}

static void	search_and_remove_vars(t_list **head, char **args)
{
	t_list	*curr;
	t_list	*previous;

	curr = *head;
	previous = NULL;
	while (*args)
	{
		while (curr && cmp_var_name(curr->content, *args) == 0)
		{
			previous = curr;
			curr = curr->next;
		}
		if (curr)
		{
			if (!previous)
				(*head) = curr->next;
			else
				previous->next = curr->next;
			free(curr->content);
			free(curr);
		}
		previous = NULL;
		curr = *head;
		args++;
	}
}

int	execute_unset(t_list **head, char *key)
{
	char	**args;

	if (key[0] == '\0')
		return (0);
	args = split_quotes_bash(key, " \t\n", NULL);
	if (trim_quotes(args) != 0)
	{
		free_double_array(args);
		return (126);
	}
	if (!args || size_double_array(args) == 0)
		return (0);
	search_and_remove_vars(head, args);
	free_double_array(args);
	return (0);
}
