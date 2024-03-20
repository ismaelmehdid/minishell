/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:27:23 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/20 17:59:26 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_redirection	get_redir_type(char *redirection)
{
	if (redirection[0] == '>' && redirection[1] == '>')
		return (APPEND);
	else if (redirection[0] == '<' && redirection[1] == '<')
		return (HERE_DOC);
	else if (redirection[0] == '>')
		return (OUT);
	else if (redirection[0] == '<')
		return (IN);
	return (1);
}

int	get_flags(t_redirection type)
{
	if (type == OUT)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	else if (type == IN)
		return (O_RDONLY);
	else
		return (O_CREAT | O_WRONLY | O_APPEND);
}

void	restore_std(int fds[2])
{
	if (fds[0] >= 0)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	if (fds[1] >= 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
}

int	dup_error(int fds[2])
{
	restore_std(fds);
	return (0);
}

int	redir_exist(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '>' || line[i] == '<')
			return (0);
		i++;
	}
	return (1);
}
