/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:45 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/01 20:37:02 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_list	*ft_lstlast(t_list *lst)
{
	int	i;
	int	j;

	j = 0;
	i = ft_lstsize(lst);
	while (j < i - 1)
	{
		lst = lst->next;
		j++;
	}
	return (lst);
}

static void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

int	execute_export(char *arg, t_list *env, char **envp)
{
	int	i;
	t_list	*new;

	i = 0;
	if (arg[0] == '\0')
	{
		execute_env(envp);
		return (0);
	}
	while (arg[i] == ' ')
		i++;
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
	{
		ft_putstr_fd("Memory allocation error\n", 2);
		return (1);
	}
	new->content = ft_strdup(arg + i);
	if (!new->content)
	{
		ft_putstr_fd("Memory allocation error\n", 2);
		free(new);
		return (1);
	}
	ft_lstadd_back(&env, new);
	return (0);
}
