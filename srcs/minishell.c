/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:05 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/18 14:20:59 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char *input;

	handle_signals();
	while (1)
	{
		input = readline("BestShell 😎 >>> ");
		//Parse the input here
		// functionality parsing ...
		if (!input)
			continue;
		if (handle_commands(input) == 1)
		{
			free(input);
			break;
		}
		free(input);
	}
	return (0);
}
