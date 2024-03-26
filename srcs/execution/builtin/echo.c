/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:32 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/25 01:40:25 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	print_arg(char *arg, int option)
{
	int		i;
	char	quote;

	i = 0;
	while (*arg == ' ' || (*arg >= 9 && *arg <= 13))
		arg++;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			quote = arg[i];
			i++;
			while (arg[i] && arg[i] != quote)
				ft_putchar_fd(arg[i++], STDOUT_FILENO);
		}
		else
			ft_putchar_fd(arg[i++], STDOUT_FILENO);
	}
	if (option)
		return (0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

static bool	check_option(char **arg)
{
	int	i;

	i = 0;
	if (arg[0][i] && arg[0][i + 1] && arg[0][i] == '-'
		&& arg[0][i + 1] == 'n')
	{
		i++;
		while (arg[0][i] == 'n')
			i++;
		if (arg[0][i] != ' ' || (arg[0][i] >= 9 && arg[0][i] <= 13))
			return (false);
		*arg = *arg + i;
		return (true);
	}
	return (false);
}

int	execute_echo(char *arg)
{
	bool	option;

	option = true;
	while (*arg == ' ' || (*arg >= 9 && *arg <= 13))
		arg++;
	if (*arg == '\0')
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	option = check_option(&arg);
	print_arg(arg, option);
	return (0);
}
