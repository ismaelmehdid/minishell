/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:05 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/18 19:11:20 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("BestShell 😎 >>> ");
		//Parsing gotta be here
		if (!input)
		{
			free(input);
			break ;
		}
		if (handle_commands(input) == 1)
		{
			free(input);
			program_exit(1);
		}
		free(input);
	}
	return (0);
}
