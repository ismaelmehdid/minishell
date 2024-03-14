/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_elements_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:41:08 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/13 02:44:11 by imehdid          ###   ########.fr       */
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

int	count_words(char *input, char *skip)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!input || !skip)
		return (0);
	while (input[i])
	{
		while (input[i] && ft_strchr(skip, input[i]))
			i++;
		if (input[i])
		{
			count++;
			if (input[i] == '\'' || input[i] == '"')
				skip_quotes(input, &i);
			else
			{
				while (input[i] && !ft_strchr(skip, input[i]))
					i++;
			}
		}
	}
	return (count);
}

char	*malloc_word(char *input, int *i, char *skip)
{
	int		nb_letters;
	char	*word;
	char	quote;

	nb_letters = 0;
	while (input[*i] && !ft_strchr(skip, input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quote = input[*i];
			nb_letters++;
			(*i)++;
			while (input[*i] && input[*i] != quote)
			{
				nb_letters++;
				(*i)++;
			}
			if (input[*i] && input[*i] == quote)
				nb_letters++;
			if (input[*i])
				(*i)++;
		}
		else
		{
			nb_letters++;
			(*i)++;
		}
	}
	word = malloc(sizeof(char) * (nb_letters + 1));
	return (word);
}

void	copy_word(char *result, char *input, int *i, char *skip)
{
	int		k;
	char	quote;

	k = 0;
	while (input[*i] && !ft_strchr(skip, input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quote = input[*i];
			result[k++] = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != quote)
			{
				result[k++] = input[*i];
				(*i)++;
			}
			if (input[*i] && input[*i] == quote)
				result[k++] = input[*i];
			if (input[*i])
				(*i)++;
		}
		else
			result[k++] = input[(*i)++];
	}
	result[k] = '\0';
}
