/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:04:09 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/27 15:27:25 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	get_return_scenario(char *delimiter, int orig_stdin, int fd)
{
	if (isatty(STDIN_FILENO))
	{
		ft_putstr_fd("minishell: warning: here-document ", 2);
		ft_putstr_fd("delimited by end-of-file ", 2);
		ft_putstr_fd("(wanted 'EOF')\n", 2);
		g_last_command_status = 0;
		free(delimiter);
		return (fd);
	}
	restore_stdin(1, orig_stdin);
	free(delimiter);
	close (fd);
	return (-500);
}

static int	here_doc_loop(char *delimiter, int fd, char *input, int orig_stdin)
{
	while (1)
	{
		signal(SIGINT, new_ctrl_c);
		input = readline("heredoc> ");
		if (!input)
			fd = get_return_scenario(delimiter, orig_stdin, fd);
		if (!input)
			break ;
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

static int	create_tmp_file(char *delimiter, int fd, int orig_stdin)
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
	if (dup2(orig_stdin, STDIN_FILENO) < 0)
		return (-1);
	fd = here_doc_loop(delimiter, fd, NULL, orig_stdin);
	signal(SIGQUIT, ctrl_back_slash);
	if (fd == -500)
		unlink_file("without");
	return (fd);
}

int	here_doc(char *delimiter, int fd, int dup_return, int orig_stdin)
{
	if (!delimiter)
		return (-1);
	fd = create_tmp_file(delimiter, 0, orig_stdin);
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

int	pre_here_doc(char *redir, int fds[2])
{
	int	stdout_fd_saved;
	int	return_value;

	stdout_fd_saved = dup(STDOUT_FILENO);
	if (stdout_fd_saved < 0)
	{
		ft_putstr_fd("dup error\n", 2);
		return (-1);
	}
	if (dup2(fds[1], STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("dup2 error\n", 2);
		close(stdout_fd_saved);
		return (-1);
	}
	return_value = here_doc(get_file_redir(redir), 0, 0, fds[0]);
	if (dup2(stdout_fd_saved, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("dup2 error\n", 2);
		close(stdout_fd_saved);
		return (-1);
	}
	close(stdout_fd_saved);
	return (return_value);
}
