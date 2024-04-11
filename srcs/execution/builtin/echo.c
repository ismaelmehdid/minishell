/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <imehdid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:32 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/11 13:28:18 by imehdid          ###   ########.fr       */
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
	trim_quotes(args);
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
