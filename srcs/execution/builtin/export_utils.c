/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:01:03 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/26 19:10:59 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] != lst->content[i])
			return (0);
		i++;
	}
	if (arg[i] && arg[i] == '=' && lst->content[i] == '=')
		return (1);
	return (0);
}
