/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:04:17 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/14 17:53:02 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	swap_nodes(t_list *node1, t_list *node2)
{
	char	*temp_content;
	bool	temp_export_marked;
	bool	temp_export_marked_sub;
	bool	temp_value_assigned;

	temp_content = node1->content;
	temp_export_marked = node1->export_marked;
	temp_export_marked_sub = node1->export_marked_sub;
	temp_value_assigned = node1->value_assigned;
	node1->content = node2->content;
	node1->export_marked = node2->export_marked;
	node1->export_marked_sub = node2->export_marked_sub;
	node1->value_assigned = node2->value_assigned;
	node2->content = temp_content;
	node2->export_marked = temp_export_marked;
	node2->export_marked_sub = temp_export_marked_sub;
	node2->value_assigned = temp_value_assigned;
}

static void	sort_list(t_list **head)
{
	t_list	*i;
	t_list	*j;

	if (!head)
		return ;
	i = *head;
	while (i != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (mystrcmp(i->content, j->content) > 0)
				swap_nodes(i, j);
			j = j->next;
		}
		i = i->next;
	}
}

static t_list	*copy_list(t_list *env, bool sub_var)
{
	t_list	*new_list;

	if (!env)
		return (NULL);
	if (env->export_marked_sub == sub_var)
	{
		new_list = malloc(sizeof(t_list));
		if (!new_list)
			return (NULL);
		new_list->content = ft_strdup(env->content);
		if (!new_list->content)
			return (free_copy_list(NULL, new_list));
		new_list->export_marked = env->export_marked;
		new_list->export_marked_sub = env->export_marked_sub;
		new_list->value_assigned = env->value_assigned;
		new_list->next = copy_list(env->next, sub_var);
		return (new_list);
	}
	new_list = copy_list(env->next, sub_var);
	if (!new_list && env->next)
		return (NULL);
	return (new_list);
}

static void	print_exported_var(t_list *env, bool sub_var)
{
	t_list	*exported_sub_list;
	t_list	*temp;
	int		i;

	exported_sub_list = copy_list(env, sub_var);
	if (!exported_sub_list)
		return ;
	temp = exported_sub_list;
	sort_list(&exported_sub_list);
	while (temp)
	{
		i = 0;
		while (temp->content[i] && temp->content[i] != '=')
			printf("%c", temp->content[i++]);
		if (temp->content[i] == '=')
		{
			printf("%c", temp->content[i++]);
			printf("\"%s\"\n", temp->content + i);
		}
		else
			printf("\n");
		temp = temp->next;
	}
	free_list(&exported_sub_list);
	free(exported_sub_list);
}

int	show_exported_var_list(t_list *env, char **exports)
{
	free_double_array(exports);
	if (!env)
		return (0);
	print_exported_var(env, true);
	print_exported_var(env, false);
	return (0);
}
