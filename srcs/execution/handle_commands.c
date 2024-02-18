/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:30:15 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/17 20:07:13 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int ctrl_c_pressed;

int	handle_commands(char *input)
{
	if (!input)
		return (1);
	if (ctrl_c_pressed)
	{
		ctrl_c_pressed = 0;
		return (0);
	}
	else if (ft_strncmp(input, "exit", ft_strlen(input) + 1) == 0)
	 	return (1);
	else if (ft_strncmp(input, "clear", ft_strlen(input) + 1) == 0)
		printf(CLEAR_SCREEN);
	return (0);
}