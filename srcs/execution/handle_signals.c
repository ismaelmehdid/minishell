/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:00:34 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/11 17:53:27 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		printf("\nI commented functions\n");
		//rl_on_new_line();
		//rl_replace_line("", 0);
		//rl_redisplay();
		return ;
	}
	else if (signum == SIGQUIT)
		return ;
}

void	handle_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static void	sig_pipes_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		printf("\nI commented functions\n");
		//rl_on_new_line();
		//rl_replace_line("", 0);
		//rl_redisplay();
		return ;
	}
	else if (signum == SIGQUIT)
		return ;
}

void	handle_pipes_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_pipes_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
