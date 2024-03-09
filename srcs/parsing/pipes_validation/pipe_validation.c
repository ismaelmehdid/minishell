/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:08:47 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/08 22:29:02 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_last_pipe_command(char *input)
{
	int	i;

	i = ft_strlen(input) - 1;
	while (i >= 0 && (input[i] == ' ' || input[i] == '\n' \
		|| input[i] == '\t' || input[i] == '\v' || \
		input[i] == '\f' || input[i] == '\r'))
		i--;
	if (i >= 0 && input[i] == '|')
		return (1);
	return (0);
}

static char	*pipes_checker(char *input, int i)
{
	if (input[i + 1] && (input[i + 2] && input[i + 3] \
		&& input[i + 1] == '|' && input[i + 2] == '|' \
		&& input[i + 3] == '|'))
	{
		ft_putstr_fd("parse error near `||'\n", 2);
		free(input);
		return (NULL);
	}
	else if (input[i + 1] && (input[i + 1] && input[i + 2]
			&& input[i + 1] == '|' && input[i + 2] == '|'))
	{
		ft_putstr_fd("parse error near `|'\n", 2);
		free(input);
		return (NULL);
	}
	return (input);
}

static char	*pipes_format_checker(char *inp)
{
	int	i;

	i = 0;
	while (inp[i] && (inp[i] == ' ' || inp[i] == '\n' || inp[i] == 9 \
			|| inp[i] == '\v' || inp[i] == '\f' || inp[i] == '\r'))
		i++;
	if (inp[i] == '|')
	{
		if (inp[i + 1] && inp[i + 1] == '|')
			ft_putstr_fd("parse error near `||'\n", 2);
		else
			ft_putstr_fd("parse error near `|'\n", 2);
		free(inp);
		return (NULL);
	}
	while (inp[i])
	{
		while (inp[i] && inp[i] != '|')
			i++;
		if (inp[i] && !pipes_checker(inp, i))
			return (NULL);
		if (inp[i])
			i++;
	}
	return (inp);
}

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
