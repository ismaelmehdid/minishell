/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:08:47 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/27 23:01:10 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*pipes_format_checker(char *input);

static char	*set_new_command(char *input)
{
	char	*new_command;
	char	*new_input;

	new_command = NULL;
	new_command = readline("pipe->");
	new_input = malloc(
			sizeof(char) * (ft_strlen(new_command) + ft_strlen(input) + 1));
	new_input = ft_strdup(input);
	ft_strlcat(new_input, new_command,
		(ft_strlen(new_command) + ft_strlen(input) + 1));
	new_input = pipes_format_checker(new_input);
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
		printf("minishell: parse error near `||'");
		free(input);
		return (NULL);
	}
	else if (input[i + 1] && (input[i + 1] && input[i + 2]
			&& input[i + 1] == '|' && input[i + 2] == '|'))
	{
		printf("minishell: parse error near `|'");
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
			printf("minishell: parse error near `||'");
		else
			printf("minishell: parse error near `|'");
		free(input);
		return (NULL);
	}
	while (input[i])
	{
		while (input[i] && input[i] != '|')
			i++;
		if (input[i] && !pipes_checker(input, i))
			return (NULL);
		i++;
	}
	if (check_last_pipe_command(input))
		input = set_new_command(input);
	return (input);
}

char	*pipes_validation(char *input)
{
	input = pipes_format_checker(input);
	printf("%s\n", input);
	return (input);
}
