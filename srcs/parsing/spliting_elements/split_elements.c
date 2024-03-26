/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:17:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/26 15:35:10 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	skip_quotes(char *input, int *i)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
		(*i)++;
}

static char	**malloc_each_arrays(char **result, char *input, char *skip, t_list *env)
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
			result[j] = malloc_word(input, &i, skip, env);
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

static void	copy_each_elements(char **result, char *input, char *skip, t_list *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		while (*input && ft_strchr(skip, *input))
			input++;
		if (*input)
		{
			input += copy_word(result[j], input, skip, env);
			j++;
		}
	}
}

char	**split_quotes(char *input, char *skip, t_list *env)
{
	char	**result;

	result = NULL;
	if (!input || !skip)
		return (NULL);
	result = malloc_each_arrays(result, input, skip, env);
	if (!result)
		return (NULL);
	copy_each_elements(result, input, skip, env);
	return (result);
}
