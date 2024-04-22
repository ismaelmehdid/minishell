/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:04:09 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/22 14:32:56 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	here_doc_loop(char *delimiter, int fd, char *input)
{
	while (1)
	{
		signal(SIGINT, new_ctrl_c);
		input = readline("heredoc> ");
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("Delimited by EOF\n", 2);
			restore_stdin(1);
			free(delimiter);
			close (fd);
			return (-500);
		}
		if (ft_strlen(input) == ft_strlen(delimiter) \
			&& ft_strnstr(input, delimiter, ft_strlen(delimiter)))
		{
			free(delimiter);
			free(input);
			break ;
		}
		if (write_to_tmp_file(fd, input) == -1)
			return (-1);
	}
	return (fd);
}

static int	create_tmp_file(char *delimiter, int fd)
{
	signal(SIGQUIT, SIG_IGN);
	fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_putstr_fd("File creation error\n", 2);
		return (-1);
	}
	close(STDIN_FILENO);
	if (dup2(g_stdin_copy_fd, STDIN_FILENO) < 0)
		return (-1);
	fd = here_doc_loop(delimiter, fd, NULL);
	signal(SIGQUIT, ctrl_back_slash);
	if (fd == -500)
		unlink_file("without");
	return (fd);
}

int	here_doc(char *delimiter, int fd, int dup_return)
{
	if (!delimiter)
		return (-1);
	fd = create_tmp_file(delimiter, 0);
	if (fd == -500)
		return (-500);
	if (fd < 0)
	{
		unlink_file("Error with a file or allocation\n");
		return (-1);
	}
	if (close(fd) < 0)
		ft_putstr_fd("File error\n", 2);
	fd = open("/tmp/heredoc", O_RDWR, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		unlink_file("File open error\n");
		return (-1);
	}
	dup_return = dup2(fd, STDIN_FILENO);
	if (dup_return < 0)
		ft_putstr_fd("File error\n", 2);
	if (close(fd) < 0)
		ft_putstr_fd("File error\n", 2);
	unlink_file("without");
	return (dup_return);
}

int	pre_here_doc(char *redir, int orig_stdout)
{
	int stdout_fd_saved;
	int	return_value;

	stdout_fd_saved = dup(STDOUT_FILENO);
	if (stdout_fd_saved < 0)
	{
		ft_putstr_fd("dup error\n", 2);
		return (-1);
	}
	if (dup2(orig_stdout, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("dup2 error\n", 2);
		close(stdout_fd_saved);
		return (-1);
	}
	return_value = here_doc(get_file_redir(redir), 0, 0);
	if (dup2(stdout_fd_saved, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("dup2 error\n", 2);
		close(stdout_fd_saved);
		return (-1);
	}
	return (return_value);
}
