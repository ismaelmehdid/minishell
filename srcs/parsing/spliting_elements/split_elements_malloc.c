/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_elements_malloc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:33:38 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/25 17:20:58 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
			while (input[i] && !ft_strchr(skip, input[i]))
			{
				if (input[i] == '\'' || input[i] == '"')
				{
					skip_quotes(input, &i);
					continue ;
				}
				i++;
			}
		}
	}
	return (count);
}

static int	handle_quote(char *input, int *i, char quote, t_list *env)
{
	int	nb_letters;

	nb_letters = 0;
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		if (input[*i] == '$' && quote == '"' && input[*i + 1]
			&& !is_whitespace(input[*i + 1])
			&& input[*i + 1] != '"' && input[*i + 1] != '\'')
			nb_letters += search_env_size(input, i, env);
		else
		{
			nb_letters++;
			(*i)++;
		}
	}
	if (input[*i] && input[*i] == quote)
		nb_letters++;
	if (input[*i])
		(*i)++;
	return (nb_letters);
}

static void	handle_no_quote(char *input, int *i, int *nb_letters, t_list *env)
{
	if (input[*i] == '$' && input[*i + 1] && !is_whitespace(input[*i + 1]
			&& input[*i + 1] != '"' && input[*i + 1] != '\''))
		*nb_letters += search_env_size(input, i, env);
	else
	{
		(*nb_letters)++;
		(*i)++;
	}
}

char	*malloc_word(char *input, int *i, char *skip, t_list *env)
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
			nb_letters += handle_quote(input, i, quote, env);
		}
		else
			handle_no_quote(input, i, &nb_letters, env);
	}
	word = ft_calloc(nb_letters + 1, sizeof(char));
	return (word);
}
