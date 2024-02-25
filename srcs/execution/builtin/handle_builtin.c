/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/25 15:51:45 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_builtin(char *input)
{
	if (ft_strncmp(input, "echo", 4) == 0)
	{
		printf("\nSoon...\n");
		if (execute_echo() == 0)
			return (0);
	}
	else if (ft_strncmp(input, "cd ", 3) == 0)
	{
		printf("\nPWD, OLDPWD in env should be changed\n");
		if (execute_cd(input + 3) == 0)
			return (0);
	}
	else if (ft_strncmp(input, "pwd", 3) == 0)
	{
		if (execute_pwd() == 0)
			return (0);
	}
	else if (ft_strncmp(input, "export", 6) == 0)
	{
		printf("\nSoon...\n");
		if (execute_export() == 0)
			return (0);
	}
	else if (ft_strncmp(input, "unset", 5) == 0)
	{
		printf("\nSoon...\n");
		if (execute_unset() == 0)
			return (0);
	}
	else if (ft_strncmp(input, "env", 3) == 0)
	{
		printf("\nNot correct implimentation\n");
		if (execute_env() == 0)
			return (0);
	}
	else if (ft_strncmp(input, "exit", 4) == 0)
	{
		printf("\nSoon...\n");
		if (execute_env() == 0)
			return (0);
	}
	return (1);
}