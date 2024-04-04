/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:21:12 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/04 01:40:22 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	write_from_stdin_to_fd(int *fd, int bytes_read, int bytes_written)
{
	char	buffer[100];

	while (bytes_read != 0)
	{
		bytes_read = read(STDIN_FILENO, buffer, 100);
		if (bytes_read == -1)
			break ;
		bytes_written = write((*fd), buffer, bytes_read);
		if (bytes_written != bytes_read)
			return (-1);
	}
	if (bytes_read == -1)
		return (-1);
	close(STDIN_FILENO);
	if (dup2(g_stdin_copy_fd, STDIN_FILENO) < 0)
		return (-1);
	return (0);
}

int	write_to_tmp_file(int fd, char *input)
{
	int	bytes_read;

	input = ft_strjoin_free(input, "\n", ft_strlen("\n"));
	if (!input)
		return (-1);
	bytes_read = write(fd, input, ft_strlen(input));
	if (bytes_read < 0)
	{
		if (input)
			free (input);
		close(fd);
		return (-1);
	}
	free(input);
	return (0);
}

void	unlink_file(char *msg)
{
	if (unlink("/tmp/heredoc") < 0)
		ft_putstr_fd("Unlinking failed\n", 2);
	if (ft_strncmp(msg, "without", 7) != 0)
		ft_putstr_fd(msg, 2);
}
