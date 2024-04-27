/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:01:03 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/27 18:55:28 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	value_exist(t_list *lst, char *arg)
{
	int	i;
	int	arg_len;
	int	env_var_len;

	arg_len = ft_strlen(arg);
	env_var_len = 0;
	while (lst)
	{
		i = -1;
		while (lst->content[env_var_len] && lst->content[env_var_len] != '=')
			env_var_len++;
		if (env_var_len == arg_len)
		{
			while (arg[++i])
			{
				if (arg[i] != lst->content[i])
					break ;
			}
			if (i == ft_strlen(arg))
				return (true);
		}
		env_var_len = 0;
		lst = lst->next;
	}
	return (false);
}

t_list	*get_last_node(t_list *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	export_print_error(char *arg)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	search_replace_existing_cmp(t_list *lst, char *arg)
{
	int	i;
	int	len;
	int	len2;

	len = 0;
	len2 = 0;
	while (arg[len2] && arg[len2] != '=' && arg[len2] != '+')
		len2++;
	while (lst->content[len] && lst->content[len] != '=')
		len++;
	if (len != len2)
		return (0);
	i = 0;
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
	{
		if (arg[i] != lst->content[i])
			return (0);
		i++;
	}
	return (1);
}

int	checking_errors(char **exports)
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
		while (exports[i][j] && exports[i][j] != '+' && exports[i][j] != '=')
		{
			if (exports[i][j] == '+' && exports[i][j + 1] == '=')
				return (0);
			if (exports[i][j] != '_' && !ft_isalnum(exports[i][j]))
				return (export_print_error(exports[i]));
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
