/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:54 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/29 18:26:00 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	invalid_parameter(char *param)
{
	int	i;

	i = 0;
	while (param[i] != '\0')
	{
		if (param[i] == '=')
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(param, 2);
			ft_putstr_fd(": invalid parameter name\n", 2);
			g_last_command_status = 128;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	create_all_keys(char *old_str, char **temp, char **new_key)
{
	temp = new_key;
	while (*temp)
	{
		old_str = *temp;
		*temp = ft_strjoin(old_str, "=");
		if (!*temp)
		{
			ft_putstr_fd("Malloc allocation error\n", 2);
			free_double_array(new_key);
			return (1);
		}
		free(old_str);
		temp++;
	}
	*temp = NULL;
	return (0);
}

static char	**create_key(char *key)
{
	char	**new_key;
	char	**temp;
	char	*old_str;

	temp = NULL;
	old_str = NULL;
	if (invalid_parameter(key) == 1)
		return (NULL);
	new_key = split_quotes(key, " \t\n\v\f\r", NULL);
	if (!new_key)
	{
		ft_putstr_fd("Malloc allocation error\n", 2);
		return (NULL);
	}
	if (trim_quotes(new_key) != 0)
		return (NULL);
	if (create_all_keys(old_str, temp, new_key) != 0)
		return (NULL);
	return (new_key);
}

static void	search_and_remove_env(t_list **head, char **args)
{
	t_list	*curr;
	t_list	*previous;

	curr = *head;
	previous = NULL;
	while (*args)
	{
		while (curr && ft_strncmp(curr->content, *args, ft_strlen(*args)) != 0)
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
	args = create_key(key);
	if (!args)
	{
		if (g_last_command_status == 128)
			return (128);
		else
			return (1);
	}
	search_and_remove_env(head, args);
	free_double_array(args);
	return (0);
}
