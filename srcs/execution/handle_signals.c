/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:00:34 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/18 19:00:19 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_ctrl_c_pressed = 0;

void	sigint_handler(int signum)
{
	(void)signum;
	g_ctrl_c_pressed = 1;
}

void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
}
