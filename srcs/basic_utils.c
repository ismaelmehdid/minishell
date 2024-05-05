/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:48:41 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/27 15:24:26 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	only_slashes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '/')
			i++;
		else
			return (1);
	}
	return (0);
}

int	only_spaces(char *line)
{
	int	i;

	i = 0;
	if (only_slashes(line) == 0 && ft_strlen(line) > 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	while (line[i])
	{
		if (is_whitespace(line[i]) || line[i] == '/')
			i++;
		else
			return (1);
	}
	return (0);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	restore_stdin(int check_num, int orig_stdin)
{
	if (check_num == 1)
		printf("\033[F\033[K");
	if (!isatty(STDIN_FILENO))
	{
		if (check_num == 0)
		{
			ft_putchar_fd('\n', 2);
			printf("\033[F\033[K");
		}
		if (check_num == 3)
		{
			if (g_last_command_status != 131)
				g_last_command_status = 130;
			ft_putchar_fd('\n', 2);
			printf("\033[F\033[K");
		}
		if (dup2(orig_stdin, STDIN_FILENO) < 0)
		{
			ft_putstr_fd("dup2 error\n", 2);
			return (-1);
		}
		return (0);
	}
	return (2);
}
