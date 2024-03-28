/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:32 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/28 17:34:22 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_arg(char *arg)
{
	char	quote;
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			quote = arg[i];
			i++;
			while (arg[i] && arg[i] != quote)
				ft_putchar_fd(arg[i++], STDOUT_FILENO);
			if (arg[i] == quote)
			{
				i++;
				while (arg[i] && !is_whitespace(arg[i]))
					ft_putchar_fd(arg[i++], STDOUT_FILENO);
			}
			break ;
		}
		ft_putchar_fd(arg[i], STDOUT_FILENO);
		i++;
	}
}

static int	print_args(char **args, int option)
{
	int		j;

	j = 0;
	if (option == true)
		j++;
	while (args[j])
	{
		print_arg(args[j]);
		if (args[j + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		j++;
	}
	if (option)
		return (0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

static bool	check_option(char *arg)
{
	int	i;

	i = 1;
	if (!arg)
		return (false);
	if (arg[0] == '-' && arg[1] != '\0')
	{
		while (arg[i] == 'n')
			i++;
		if (i > 1 && arg[i] == '\0')
			return (true);
	}
	return (false);
}

int	execute_echo(char *arg)
{
	bool	option;
	char	**args;

	option = true;
	args = split_quotes(arg, " \t\n\v\f\r", NULL);
	if (args == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	option = check_option(args[0]);
	print_args(args, option);
	free_double_array(args);
	return (0);
}
