/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_elements_copy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:33:27 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/29 17:52:10 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	handle_quotes(
	char *input,
	char *result,
	t_cpy_word_indexes *indexes,
	t_list *env)
{
	char	quote;

	quote = input[indexes->i];
	result[indexes->k++] = input[indexes->i++];
	while (input[indexes->i] && input[indexes->i] != quote)
	{
		if (quote == '"' && input[indexes->i] == '$')
			add_env_value(result, input, indexes, env);
		else
		{
			result[indexes->k] = input[indexes->i];
			indexes->i++;
			indexes->k++;
		}
	}
	if (input[indexes->i] && input[indexes->i] == quote)
		result[indexes->k++] = input[indexes->i];
	if (input[indexes->i])
		indexes->i++;
}

int	copy_word(char *result, char *input, char *skip, t_list *env)
{
	t_cpy_word_indexes	indexes;

	indexes.i = 0;
	indexes.k = 0;
	while (input[indexes.i] && !ft_strchr(skip, input[indexes.i]))
	{
		if (input[indexes.i] == '\'' || input[indexes.i] == '"')
			handle_quotes(input, result, &indexes, env);
		else if (input[indexes.i] == '$')
			add_env_value(result, input, &indexes, env);
		else
			result[indexes.k++] = input[indexes.i++];
	}
	result[indexes.k] = '\0';
	return (indexes.i);
}
