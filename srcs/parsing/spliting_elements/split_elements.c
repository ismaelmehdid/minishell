/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:17:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/03 18:09:04 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	**malloc_each_arrays(char **result, char *input, char *skip)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * (count_words(input, skip) + 1));
	if (!result)
		return (NULL);
	while (input[i])
	{
		while (input[i] && ft_strchr(skip, input[i]))
			i++;
		if (input[i])
		{
			result[j] = malloc_word(input, &i, skip);
			if (!result[j])
			{
				free_double_array(result);
				return (NULL);
			}
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}

static void	copy_each_elements(char **result, char *input, char *skip)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] && ft_strchr(skip, input[i]))
			i++;
		if (input[i])
		{
			copy_word(result[j], input, &i, skip);
			j++;
		}
	}
}

char	**split_quotes(char *input, char *skip)
{
	char	**result;

	result = NULL;
	if (!input || !skip)
		return (NULL);
	result = malloc_each_arrays(result, input, skip);
	if (!result)
		return (NULL);
	copy_each_elements(result, input, skip);
	return (result);
}
