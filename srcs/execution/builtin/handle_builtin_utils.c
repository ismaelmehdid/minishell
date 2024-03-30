/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:25:04 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/30 19:17:00 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_cmd_args_index(char *input)
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

static char	*initialize_new_string(char **args, int j, int *i, int *e)
{
	char	*new;

	*i = 0;
	*e = 0;
	new = malloc(ft_strlen(args[j]) - 2 + sizeof(char));
	if (!new)
		return (NULL);
	while (args[j][*i] && args[j][*i] != '\'' && args[j][*i] != '"')
		new[(*e)++] = args[j][(*i)++];
	return (new);
}

static int	trim_quotes_utils(char **args, int j, char *new)
{
	char	quote;
	int		i;
	int		e;

	new = initialize_new_string(args, j, &i, &e);
	if (!new)
		return (1);
	if (args[j][i] == '\0')
	{
		free (new);
		return (0);
	}
	quote = args[j][i++];
	while (args[j][i] && args[j][i] != quote)
		new[e++] = args[j][i++];
	if (args[j][i++] == quote)
	{
		while (args[j][i] && !is_whitespace(args[j][i]))
			new[e++] = args[j][i++];
		new[e] = '\0';
	}
	free (args[j]);
	args[j] = new;
	return (0);
}

int	trim_quotes(char **args)
{
	int		j;
	char	*new;

	j = 0;
	new = NULL;
	if (!args)
		return (1);
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
