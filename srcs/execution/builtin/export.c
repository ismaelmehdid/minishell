/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:45 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/06 20:15:30 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	printlist(t_list *lst)
{
	while (lst->next)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
		
}

static int	search_replace_existing_cmp(t_list *lst, char *arg)
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

static int	search_replace_existing(t_list **lst, char *arg)
{
	t_list	*current;

	current = *lst;
	while (*arg && (*arg == ' ' || (*arg >= 9 && *arg <= 13)))
		arg++;
	printlist(*lst);
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
	int		i;
	t_list	*new;

	i = 0;
	if (arg[0] == '\0')
	{
		execute_env(envp);
		return (0);
	}
	if (search_replace_existing(&env, arg))
		return (0);
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
