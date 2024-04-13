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
