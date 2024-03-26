/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:25:04 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/26 19:11:45 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_command_args_indexes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i] && !is_whitespace(input[i]))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			i++;
			while (input[i] != quote)
				i++;
			if (input[i] == quote)
				i++;
		}
		else
			i++;
	}
	return (i);
}

int	get_command(char *input, char *checking)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (input[i] && !is_whitespace(input[i]))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
			{
				if (input[i++] != checking[j++])
					return (1);
			}
			if (input[i] == quote)
				i++;
		}
		else if (input[i++] != checking[j++])
			return (1);
	}
	if (checking[j] != '\0')
		return (1);
	return (0);
}

static int	trim_quotes_utils(char **args, int j, char *new)
{
	if (args[j][0] == '"')
	{
		new = ft_strtrim(args[j], "\"");
		if (!new)
			return (1);
		free(args[j]);
		args[j] = ft_strdup(new);
		if (!new)
			return (1);
	}
	else if (args[j][0] == '\'')
	{
		new = ft_strtrim(args[j], "'");
		if (!new)
			return (1);
		free(args[j]);
		args[j] = ft_strdup(new);
		if (!args[j])
			return (1);
	}
	return (0);
}

int	trim_quotes(char **args)
{
	int		j;
	char	*new;

	j = 0;
	new = NULL;
	while (args[j])
	{
		if (trim_quotes_utils(args, j, new))
			return (1);
		if (new)
		{
			free(new);
			new = NULL;
		}
		j++;
	}
	return (0);
}
