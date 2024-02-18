/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:05 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/18 14:05:57 by asyvash          ###   ########.fr       */
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
        add_history(input);
        // test comment
		//gotta put the parsing and execution here
        free(input);
    }
    clear_history();
	return (0);
}