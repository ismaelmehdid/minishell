/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:38 by asyvash           #+#    #+#             */
/*   Updated: 2024/02/27 23:23:09 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	execute_env(void)
{
	pid_t		pid;
	extern char	**environ;
	char		**args;

	args = (char *[]){"/usr/bin/env", NULL};
	pid = fork();
	if (pid == -1)
	{
		perror("Fork problem in execute_env");
		return (1);
	}
	else if (pid == 0)
	{
		if (execve("/usr/bin/env", args, environ) == -1)
		{
			perror("execve problem in execute_env");
			return (1);
		}
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}
