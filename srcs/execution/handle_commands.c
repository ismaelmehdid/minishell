/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:30:15 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/18 15:19:40 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int ctrl_c_pressed;

static void	print_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int	handle_commands(char *input, char **envp)
{
	if (!input)
		return (1);
	if (handle_bultin(input))
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
	else if (ft_strncmp(input, "env", ft_strlen(input) + 1) == 0)
		print_env(envp);
	return (0);
}