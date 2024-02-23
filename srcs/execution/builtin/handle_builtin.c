/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/22 18:12:18 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_builtin(char *input)
{
	if (ft_strncmp(input, "exit", ft_strlen(input) + 1) == 0)
		return (1);
	else if (ft_strncmp(input, "pwd", ft_strlen(input) + 1) == 0)
	{
		if (execute_pwd())
			return (1);
	}
	else if (ft_strncmp(input, "export", ft_strlen(input) + 1) == 0)
	{
		if (execute_export())
			return (1);
	}
	else if (ft_strncmp(input, "env", ft_strlen(input) + 1) == 0)
	{
		if (execute_env())
			return (1);
	}
	else if (ft_strncmp(input, "unset", ft_strlen(input) + 1) == 0)
	{
		if (execute_unset())
			return (1);
	}
	else if (ft_strncmp(input, "clear", ft_strlen(input) + 1) == 0)
		printf(CLEAR_SCREEN);
	return (0);
}
