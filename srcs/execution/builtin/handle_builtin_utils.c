/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:25:04 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/04 00:08:55 by imehdid          ###   ########.fr       */
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

static char	*initialize_new_string(char *args, int *i, int *e)
{
	char	*new;

	*i = 0;
	*e = 0;
	new = malloc(ft_strlen(args) - 2 + sizeof(char));
	if (!new)
		return (NULL);
	while (args[*i] && args[*i] != '\'' && args[*i] != '"')
		new[(*e)++] = args[(*i)++];
	return (new);
}

static int	trim_quotes_utils(char **args, char *new)
{
	char	quote;
	int		i;
	int		e;

	new = initialize_new_string(*args, &i, &e);
	if (!new)
		return (1);
	if (args[0][i] == '\0')
	{
		free (new);
		return (0);
	}
	quote = args[0][i++];
	while (args[0][i] && args[0][i] != quote)
		new[e++] = args[0][i++];
	if (args[0][i++] == quote)
	{
		while (args[0][i] && !is_whitespace(args[0][i]))
			new[e++] = args[0][i++];
		new[e] = '\0';
	}
	free (args[0]);
	*args = new;
	return (0);
}

int	trim_quotes(char **args)
{
	int		j;
	char	*new;
	int		i;

	i = 0;
	j = 0;
	new = NULL;
	if (!args)
		return (1);
	while (args[j])
	{
		while (args[j][i] && args[j][i] != '\'' && args[j][i] != '"')
			i++;
		if (args[j][i] && trim_quotes_utils(&args[j], new))
			return (1);
		if (new)
		{
			free(new);
			new = NULL;
		}
		i = 0;
		j++;
	}
	return (0);
}
