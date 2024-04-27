/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:45 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/27 17:01:42 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	add_to_env(char *arg, t_list **env, bool assigned_value)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
	{
		ft_putstr_fd("Allocation error\n", 2);
		return (126);
	}
	new->content = ft_strdup(arg);
	if (!new->content)
	{
		free(new);
		return (126);
	}
	new->value_assigned = assigned_value;
	new->export_marked = true;
	new->export_marked_sub = false;
	if (*env)
		get_last_node(*env)->next = new;
	else
		*env = new;
	new->next = NULL;
	return (0);
}

static int	search_replace_existing_loop(t_list **lst, char *arg)
{
	t_list	*current;

	current = *lst;
	if (current == NULL)
		return (0);
	while (current)
	{
		if (search_replace_existing_cmp(current, arg))
		{
			free(current->content);
			current->content = ft_strdup(arg);
			current->value_assigned = true;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

static int	search_replace_existing(t_list **lst, char *arg)
{
	int		i;

	i = 0;
	if (!arg || ft_strlen(arg) == 0)
		return (1);
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '\0')
	{
		if (value_exist(*lst, arg) == false)
			add_to_env(arg, lst, false);
		return (1);
	}
	if (search_replace_existing_loop(lst, arg) != 0)
		return (1);
	return (0);
}

static int	execute_export_utils(char **exports, t_list **env)
{
	int	i;

	i = 0;
	while (exports[i])
	{
		if (search_replace_existing(env, exports[i]))
			i++;
		else
		{
			if (add_to_env(exports[i], env, true))
			{
				free_double_array(exports);
				return (126);
			}
			i++;
		}
	}
	return (0);
}

int	execute_export(char *arg, t_list **env)
{
	char	**exports;

	exports = split_quotes_bash(arg, " \t\n", NULL);
	if (trim_quotes(exports) != 0)
	{
		free_double_array(exports);
		return (126);
	}
	if (!exports || size_double_array(exports) == 0)
		return (show_exported_var_list(*env, exports));
	if (checking_errors(exports))
	{
		free_double_array(exports);
		return (1);
	}
	if (execute_export_utils(exports, env))
	{
		free_double_array(exports);
		return (126);
	}
	free_double_array(exports);
	return (0);
}
