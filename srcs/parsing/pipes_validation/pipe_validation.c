/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:08:47 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/29 16:17:14 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*pipes_format_checker(char *input);

static char	*set_new_command(char *input)
{
	char		*new_input;
	char		*new_command;

	new_input = NULL;
	new_command = readline("pipe->");
	if (!pipes_format_checker(new_command))
	{
		free(input);
		return (NULL);
	}
	new_input = malloc(ft_strlen(input) + ft_strlen(new_command) + 1);
	if (!new_input)
	{
		free(input);
		return (NULL);
	}
	ft_strlcpy(new_input, input, ft_strlen(new_input) + ft_strlen(input) + 1);
	ft_strlcat(new_input, new_command,
		ft_strlen(new_input) + ft_strlen(new_command) + 1);
	free(input);
	return (new_input);
}

static int	check_last_pipe_command(char *input)
{
	int	i;

	i = ft_strlen(input) - 1;
	while (i >= 0 && (input[i] == ' ' || input[i] == '\n' || input[i] == '\t'
			|| input[i] == '\v' || input[i] == '\f' || input[i] == '\r'))
		i--;
	if (i >= 0 && input[i] == '|')
		return (1);
	return (0);
}

static char	*pipes_checker(char *input, int i)
{
	if (input[i + 1] && (input[i + 2] && input[i + 3] && input[i + 1] == '|'
			&& input[i + 2] == '|' && input[i + 3] == '|'))
	{
		printf("minishell: parse error near `||'\n");
		free(input);
		return (NULL);
	}
	else if (input[i + 1] && (input[i + 1] && input[i + 2]
			&& input[i + 1] == '|' && input[i + 2] == '|'))
	{
		printf("minishell: parse error near `|'\n");
		free(input);
		return (NULL);
	}
	return (input);
}

static char	*pipes_format_checker(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\n' || input[i] == 9
			|| input[i] == '\v' || input[i] == '\f' || input[i] == '\r'))
		i++;
	if (input[i] == '|')
	{
		if (input[i + 1] && input[i + 1] == '|')
			printf("minishell: parse error near `||'\n");
		else
			printf("minishell: parse error near `|'\n");
		free(input);
		return (NULL);
	}
	while (input[i])
	{
		while (input[i] && input[i] != '|')
			i++;
		if (input[i] && !pipes_checker(input, i))
			return (NULL);
		if (input[i])
			i++;
	}
	return (input);
}

char	*pipes_validation(char *input)
{
	input = pipes_format_checker(input);
	while (input && check_last_pipe_command(input))
	{
		input = set_new_command(input);
		if (input)
			input = pipes_format_checker(input);
	}
	return (input);
}
