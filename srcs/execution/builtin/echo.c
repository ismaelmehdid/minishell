/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:32 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/01 20:36:41 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int print_arg(char *arg, int i, int option)
{
	while (arg[i] != '\0')
	{
		ft_putchar_fd(arg[i], STDOUT_FILENO);
		i++;
	}
	if (option == 0)
		return (0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

static int	prepare_echo(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '\0')
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (-1);
	}
	while (arg[i] == ' ')
		i++;
	if (arg[i] == '-' && arg[i + 1] != 'n')
	{
		ft_putstr_fd("echo: bad option\n", STDERR_FILENO);
		return (-2);
	}
	return (i);
}

int	execute_echo(char *arg)
{
	int i;
	int	option;

	i = prepare_echo(arg);
	option = 1;
	if (i == -2)
		return (2);
	else if (i == -1)
		return (0);
	if (arg[i] == '-' && arg[i + 1] == 'n')
	{
		i++;
		while (arg[i] == 'n')
			i++;
		if (arg[i] != ' ' && arg[i] != '\0')
		{
			ft_putstr_fd("echo: bad option h\n", STDERR_FILENO);
			return (2);
		}
		option = 0;
		i++;
	}
	print_arg(arg, i, option);
	return (0);
}