/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:05 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/15 22:48:53 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	char *input;

	while (1) {
        input = readline("BestShell 😎 >>> ");
        if (input == NULL || ft_strncmp(input, "exit", ft_strlen(input) + 1) == 0) {
            free(input);
            break;
        }
		//gotta put the parsing and execution here
        free(input);
    }
	return (0);
}