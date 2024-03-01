/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:00:34 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/01 20:43:06 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_handler(int signum)
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
