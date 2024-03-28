/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_elements_copy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:33:27 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/28 17:44:05 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	copy_word(char *result, char *input, char *skip, t_list *env)
{
	int		k;
	int		i;
	char	quote;

	i = 0;
	k = 0;
	while (input[i] && !ft_strchr(skip, input[i]))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			result[k++] = input[i++];
			while (input[i] && input[i] != quote)
			{
				if (quote == '"' && input[i] == '$')
					add_env_value(result, input, &i, &k, env);
				else
				{
					result[k++] = input[i];
					i++;
				}
			}
			if (input[i] && input[i] == quote)
				result[k++] = input[i];
			if (input[i])
				i++;
		}
		else if (input[i] == '$')
			add_env_value(result, input, &i, &k, env);
		else
			result[k++] = input[i++];
	}
	result[k] = '\0';
	return (i);
}