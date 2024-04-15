/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:58:03 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/14 17:59:11 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize(t_list *lst, bool count_only_env)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		if (count_only_env == true && lst->export_marked == true
			&& lst->value_assigned == true)
			count++;
		lst = lst->next;
	}
	return (count);
}

void	free_list(t_list **env)
{
	t_list	*temp;

	while ((*env) != NULL)
	{
		temp = (*env);
		(*env) = (*env)->next;
		free(temp->content);
		free(temp);
	}
}
