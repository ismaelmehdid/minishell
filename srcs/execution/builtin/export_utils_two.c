/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:03:32 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/14 17:53:24 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
