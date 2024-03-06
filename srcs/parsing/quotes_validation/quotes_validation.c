/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:30:16 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/02 16:01:44 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	element_quotes_checker(char *element)
{
	int		i;
	char	quote;

	i = 0;
	while (element[i])
	{
		if (element[i] == '\'' || element[i] == '"')
		{
			quote = element[i];
			i++;
			while (element[i] && element[i] != quote)
				i++;
			if (element[i] == '\0')
			{
				printf("minishell: quotes are not closed near: %c\n", quote);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	quotes_validation(char **elements)
{
	int	i;

	i = 0;
	while (elements[i])
	{
		if (element_quotes_checker(elements[i]))
			return (1);
		i++;
	}
	return (0);
}