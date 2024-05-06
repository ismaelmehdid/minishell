/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <imehdid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:45 by asyvash           #+#    #+#             */
/*   Updated: 2024/05/05 13:20:18 by imehdid          ###   ########.fr       */
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
	new->content = cpy_new_env(arg);
	if (!new->content)
	{
		free(new);
		return (126);
	}
	new->value_assigned = assigned_value;
	new->export_marked = true;
	new->export_marked_sub = false;
	new->export_excluded = false;
	if (*env)
		get_last_node(*env)->next = new;
	else
		*env = new;
	new->next = NULL;
	return (0);
}

static int	search_replace_existing_loop(t_list **lst, char *arg, bool append)
{
	t_list	*current;

	current = *lst;
	if (current == NULL)
		return (0);
	while (current)
	{
		if (search_replace_existing_cmp(current, arg))
		{
			if (append == true)
				return (append_export(current, arg));
			return (replace_export(current, arg));
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
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
		i++;
	if (arg[i] == '\0')
	{
		if (value_exist(*lst, arg) == false)
			add_to_env(arg, lst, false);
		return (1);
	}
	if (arg[i] == '+' && arg[i + 1] == '=')
	{
		if (search_replace_existing_loop(lst, arg, true) != 0)
			return (1);
		return (0);
	}
	if (search_replace_existing_loop(lst, arg, false) != 0)
		return (1);
	return (0);
}

static int	execute_export_utils(char **exports, t_list **env, int i, int error)
{
	while (exports[i])
	{
		if (checking_errors(exports[i]) == 0)
		{
			if (search_replace_existing(env, exports[i]))
			{
				i++;
				continue ;
			}
			else if (add_to_env(exports[i], env, true))
			{
				free_double_array(exports);
				return (1);
			}
		}
		else
			error++;
		i++;
	}
	if (error > 0)
		return (1);
	return (0);
}

int	execute_export(char *arg, t_list **env)
{
	char	**exports;

	exports = split_quotes_bash(arg, " \t\n", NULL);
	if (trim_quotes(exports, false) != 0)
	{
		free_double_array(exports);
		return (126);
	}
	if (!exports || size_double_array(exports) == 0)
		return (show_exported_var_list(*env, exports));
	if (execute_export_utils(exports, env, 0, 0))
	{
		free_double_array(exports);
		return (1);
	}
	free_double_array(exports);
	return (0);
}
