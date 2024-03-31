/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:00:34 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/31 21:08:46 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctrl_c(int signum)
{
	g_last_command_status = 130;
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	new_ctrl_c_pipe(int signum)
{
	g_last_command_status = 130;
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		close(STDIN_FILENO);
	}
}

void	new_ctrl_c(int signum)
{
	g_last_command_status = 130;
	if (signum == SIGINT)
		close(STDIN_FILENO);
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
