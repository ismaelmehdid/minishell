/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <imehdid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:25:04 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/11 13:43:15 by imehdid          ###   ########.fr       */
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

static int	get_new_size(char *arg)
{
	int		i;
	int		size;
	char	quote;

	i = 0;
	size = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			quote = arg[i];
			i++;
			while (arg[i] != quote)
			{
				size++;
				i++;
			}
			i++;
			continue ;
		}
		else
			size++;
		i++;
	}
	return (size);
}

static char	*get_new_arg(char **args, int index, int new_size)
{
	int		j;
	int		i;
	char	quote;
	char	*new_arg;

	j = 0;
	i = 0;
	new_arg = malloc((sizeof(char) * new_size) + sizeof(char));
	if (new_arg == NULL)
		return (NULL);
	while (args[index][i])
	{
		if (args[index][i] == '\'' || args[index][i] == '"')
		{
			quote = args[index][i++];
			while (args[index][i] != quote)
				new_arg[j++] = args[index][i++];
			i++;
			continue ;
		}
		new_arg[j++] = args[index][i++];
	}
	new_arg[j] = '\0';
	free (args[index]);
	return (new_arg);
}

int	trim_quotes(char **args, bool in_here_doc)
{
	int		j;
	int		new_size;

	j = 0;
	new_size = 0;
	if (!args)
		return (1);
	while (args[j])
	{
		new_size = get_new_size(args[j]);
		if (new_size != ft_strlen(args[j]))
			args[j] = get_new_arg(args, j, new_size);
		if (in_here_doc == true)
			return (0);
		j++;
	}
	return (0);
}
