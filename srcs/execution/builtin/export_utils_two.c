/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <imehdid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:03:32 by imehdid           #+#    #+#             */
/*   Updated: 2024/05/05 14:02:39 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	append_export(t_list *current, char *arg)
{
	if (current->value_assigned == true)
	{
		current->content = ft_strjoin_free(
				current->content, arg + get_value_index(arg),
				ft_strlen(arg + get_value_index(arg)));
	}
	else
	{
		current->content = ft_strjoin_free(
				current->content, "=", sizeof(char));
		current->content = ft_strjoin_free(
				current->content, arg + get_value_index(arg),
				ft_strlen(arg + get_value_index(arg)));
	}
	if (current->content == NULL)
	{
		ft_putstr_fd("Malloc error\n", STDERR_FILENO);
		return (2);
	}
	return (1);
}

int	replace_export(t_list *current, char *arg)
{
	free(current->content);
	current->content = ft_strdup(arg);
	if (current->content == NULL)
	{
		ft_putstr_fd("Malloc error\n", STDERR_FILENO);
		return (2);
	}
	current->value_assigned = true;
	return (1);
}

int	get_value_index(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=' && var[i] != '+')
		i++;
	if (var[i] == '=')
		return (i + 1);
	if (var[i] == '+')
		return (i + 2);
	return (0);
}

t_list	*free_copy_list(char *content, t_list *listptr)
{
	if (content)
		free(content);
	if (listptr)
		free(listptr);
	return (NULL);
}

int	mystrcmp(const char *first, const char *second)
{
	while (*first && (*first == *second))
	{
		first++;
		second++;
	}
	return (*(unsigned char *)first - *(unsigned char *)second);
}
