/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:32 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/27 17:56:10 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_arg(char **args, int i, int j)
{
	char	quote;

	while (args[j][i])
	{
		if (args[j][i] == '\'' || args[j][i] == '"')
		{
			quote = args[j][i++];
			while (args[j][i] && args[j][i] != quote)
				ft_putchar_fd(args[j][i++], STDOUT_FILENO);
			break;
		}
		ft_putchar_fd(args[j][i++], STDOUT_FILENO);
	}
	if (args[j + 1] != NULL)
		ft_putchar_fd(' ', STDOUT_FILENO);
}

static int	print_args(char **args, int option)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (option == true)
		j++;
	while (args[j])
	{
		print_arg(args, i, j);
		i = 0;
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
