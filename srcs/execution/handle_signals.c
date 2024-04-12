/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:00:34 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/12 16:25:25 by imehdid          ###   ########.fr       */
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

void	new_ctrl_c(int signum)
{
	g_last_command_status = 130;
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		close(STDIN_FILENO);
	}
}

void	ctrl_back_slash(int signum)
{
	if (signum == SIGQUIT)
	{
		close(STDIN_FILENO);
		g_last_command_status = 131;
		ft_putstr_fd("\nQuit (core dumped)\n", 2);
	}
}
