/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:38 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/15 18:36:14 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	execute_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i] != NULL)
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}
