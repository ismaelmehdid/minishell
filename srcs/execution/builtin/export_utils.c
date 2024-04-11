/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <imehdid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:01:03 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/11 14:43:05 by imehdid          ###   ########.fr       */
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
	int	len;
	int	len2;

	len = 0;
	len2 = 0;
	while (arg[len2] && arg[len2] != '=')
		len2++;
	while (lst->content[len] && lst->content[len] != '=')
		len++;
	if (len != len2)
		return (0);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] != lst->content[i])
			return (0);
		i++;
	}
	if (arg[i] == '=' && lst->content[i] == '=')
		return (1);
	return (0);
}
