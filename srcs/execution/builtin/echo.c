/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:32 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/13 18:52:36 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_arg(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		ft_putchar_fd(arg[i], STDOUT_FILENO);
		i++;
	}
}

static int	print_args(char **args, int option)
{
	int		j;

	j = 0;
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

static bool	check_option(char **arg, int *args_index)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!arg)
		return (false);
	while (arg[j])
	{
		if (arg[j][0] == '-' && arg[j][1] != '\0')
		{
			while (arg[j][i] == 'n')
				i++;
			if (i > 1 && arg[j][i] == '\0')
				(*args_index)++;
			else
				break ;
		}
		i = 1;
		j++;
	}
	if (*args_index > 0)
		return (true);
	return (false);
}

int	execute_echo(char *arg)
{
	bool	option;
	char	**args;
	int		args_index;

	args_index = 0;
	option = true;
	args = split_quotes(arg, " \t\n\v\f\r", NULL);
	trim_quotes(args);
	if (args == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	option = check_option(args, &args_index);
	print_args(args + args_index, option);
	free_double_array(args);
	return (0);
}
