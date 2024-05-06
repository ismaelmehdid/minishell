/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:32 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/26 23:59:34 by asyvash          ###   ########.fr       */
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

static bool	is_an_option(char *arg)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(arg);
	if (!arg || size == 0)
		return (false);
	if (arg[i] == '-')
	{
		i++;
		while (arg[i] && arg[i] == 'n')
			i++;
		if (i != size)
			return (false);
	}
	else
		return (false);
	return (true);
}

static bool	check_option(char **arg, int *args_index)
{
	int	j;

	j = 0;
	while (is_an_option(arg[j]))
	{
		(*args_index)++;
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
	args = split_quotes_bash(arg, " \t\n", NULL);
	trim_quotes(args, false);
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
