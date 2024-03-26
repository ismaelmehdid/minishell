/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:45 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/26 18:34:00 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	search_replace_existing(t_list **lst, char *arg)
{
	int		i;
	t_list	*current;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '\0')
		return (1);
	current = *lst;
	while (current->next)
	{
		if (search_replace_existing_cmp(current, arg))
		{
			free(current->content);
			current->content = ft_strdup(arg);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

static int	checking_errors(char **exports)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (exports[i])
	{
		if (exports[i][0] == '='
			|| (exports[i][0] != '_' && !ft_isalpha(exports[i][0])))
			return (export_print_error(exports[i]));
		while (exports[i][j] && exports[i][j] != '=')
		{
			if (exports[i][j] != '_' && !ft_isalnum(exports[i][j]))
				return (export_print_error(exports[i]));
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

static int	add_to_env(char *arg, t_list **env)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
	{
		ft_putstr_fd("Memory allocation error\n", 2);
		return (126);
	}
	new->content = ft_strdup(arg);
	if (!new->content)
	{
		ft_putstr_fd("Memory allocation error\n", 2);
		free(new);
		return (126);
	}
	if (*env)
		get_last_node(*env)->next = new;
	else
		*env = new;
	return (0);
}

int	execute_export_utils(char **exports, t_list *env)
{
	int	i;

	i = 0;
	while (exports[i])
	{
		if (search_replace_existing(&env, exports[i]))
			i++;
		else
		{
			if (add_to_env(exports[i], &env))
			{
				free_double_array(exports);
				return (126);
			}
			i++;
		}
	}
	return (0);
}

int	execute_export(char *arg, t_list *env, char **envp)
{
	char	**exports;

	exports = split_quotes(arg, " \t\n\v\f\r", NULL);
	if (!exports || size_double_array(exports) == 0)
	{
		execute_env(envp);
		return (0);
	}
	if (trim_quotes(exports) != 0)
		return (126);
	if (checking_errors(exports))
	{
		free_double_array(exports);
		return (128);
	}
	if (execute_export_utils(exports, env))
		return (126);
	return (0);
}
