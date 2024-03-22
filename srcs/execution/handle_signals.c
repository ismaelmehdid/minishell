/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:00:34 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/23 00:18:37 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_num(int num1, int num2)
{
	if (num1 == num2)
	{
		printf("\033[F\033[K");
		return (0);
	}
	return (1);
}

void	ctrl_c(int signum)
{
	g_last_command_status = 130;
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		print_prompt(g_last_command_status);
	}
}

void	new_ctrl_c_pipe(int signum)
{
	int	bytes;
	
	g_last_command_status = 130;
	if (signum == SIGINT)
	{
		if (g_sig_pressed == INT_MIN)
			g_sig_pressed = 0;
		g_sig_pressed -= 2;
		bytes = write(STDIN_FILENO, "\n", 1);
		if (bytes < 0)
			ft_putstr_fd("write() failed\n", 2);
		close(STDIN_FILENO);
	}
}

void	new_ctrl_c(int signum)
{
	g_last_command_status = 130;
	if (signum == SIGINT)
	{
		close(STDIN_FILENO);
		if (g_sig_pressed == INT_MAX)
			g_sig_pressed = 0;
		g_sig_pressed++;
	}
}

int	toggle_echoctl_status(int status)
{
	struct termios	termios_settings;

	if (tcgetattr(STDOUT_FILENO, &termios_settings) == -1)
		return (-1);
	if (status == 0)
		termios_settings.c_lflag |= ECHOCTL;
	else
		termios_settings.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &termios_settings) == -1)
		return (-1);
	return (0);
}
