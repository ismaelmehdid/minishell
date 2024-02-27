/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/27 23:23:00 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_builtin(char *input)
{
	if (ft_strcmp(input, "echo"))
	{
		printf("\nSoon...\n");
		if (execute_echo() == 0)
			return (0);
	}
	else if (ft_strcmp(input, "cd"))
	{
		printf("\nPWD, OLDPWD in env should be changed\n");
		if (execute_cd(input + 3) == 0)
			return (0);
	}
	else if (ft_strcmp(input, "pwd"))
	{
		if (execute_pwd() == 0)
			return (0);
	}
	else if (ft_strcmp(input, "export"))
	{
		printf("\nSoon...\n");
		if (execute_export() == 0)
			return (0);
	}
	else if (ft_strcmp(input, "unset"))
	{
		printf("\nSoon...\n");
		if (execute_unset() == 0)
			return (0);
	}
	else if (ft_strcmp(input, "env"))
	{
		printf("\nNot correct implimentation\n");
		if (execute_env() == 0)
			return (0);
	}
	else if (ft_strcmp(input, "exit"))
	{
		printf("\nSoon...\n");
		if (execute_unset() == 0)
			return (0);
	}
	return (1);
}
