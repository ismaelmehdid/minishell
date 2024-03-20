/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_modify_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:15:22 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/20 00:55:51 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_out(char *input)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (input[i] != '\0')
	{
		if (input[i + 1] && input[i] == '>' && \
			input[i + 1] != '>')
		{
			count++;
            while (is_whitespace(input[i]))
                i++;
		}
		i++;
	}
	return (count);
}

int count_append(char *input)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (input[i] != '\0')
	{
		if (input[i + 1] && input[i] == '>' && \
			input[i + 1] == '>')
		{
			count++;
            while (is_whitespace(input[i]))
                i++;
		}
		i++;
	}
	return (count);
}

int get_next_index(char *line, int last)
{
	static int i;
	int return_value;
	
	if (!i)
		i = 0;
	while (i != last)
	{
		if (line[i] == '>')
		{
			return_value = i;
			i++;
			if (line[i] == '>')
				i++;
			return (return_value);
			break ;
		}
		i++;
	}
	if (i == last)
		i = 0;
	return (-1);
}

int get_last_index(char *input)
{
	int i;

	i = ft_strlen(input) - 1;
	while (i >= 0 && input[i] != '>')
		i--;
	while (input[i] == '>')
		i--;
	return (i);
}

int get_prelast_file(char *input, int i)
{
	while (input[i] == '>' || input[i] == '<')
		i--;
	while (is_whitespace(input[i]))
    	i--;
	while(input[i] != '>')
		i--;
	return (i + 1);
}