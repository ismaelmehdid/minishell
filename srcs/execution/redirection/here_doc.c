/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:04:09 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/14 23:23:13 by asyvash          ###   ########.fr       */
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

static int	create_tmp_file(char *delimiter, int fd, int in_flag)
{
	signal(SIGQUIT, SIG_IGN);
	fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_putstr_fd("File creation error\n", 2);
		return (-1);
	}
	if (in_flag >= 0)
	{
		close(STDIN_FILENO);
		if (dup2(g_stdin_copy_fd, STDIN_FILENO) < 0)
			return (-1);
	}
	fd = here_doc_loop(delimiter, fd, NULL);
	signal(SIGQUIT, ctrl_back_slash);
	if (fd == -500)
		unlink_file("without");
	return (fd);
}

int	here_doc(char *delimiter, int fd, int dup_return, int in_flag)
{
	if (!delimiter)
		return (-1);
	fd = create_tmp_file(delimiter, 0, in_flag);
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

static int	pre_here_doc_2(char **redirs, int i, int quantity, int orig_stdout)
{
	int	status;
	int	check_val;
	int	stdout_copy_fd;

	check_val = if_there_was_out_append(redirs, i);
	if (i - 1 >= 0 && check_val == 0)
	{
		stdout_copy_fd = dup(STDOUT_FILENO);
		if (dup2(orig_stdout, STDOUT_FILENO) < 0)
			return (-1);
		status = here_doc(get_file_redir(redirs[i]), 0, 0, 1);
		if (dup2(stdout_copy_fd, STDOUT_FILENO) < 0)
			return (-1);
		close (stdout_copy_fd);
	}
	else if (quantity == 0)
		status = here_doc(get_file_redir(redirs[i]), 0, 0, -1);
	else
		status = here_doc(get_file_redir(redirs[i]), 0, 0, 1);
	return (status);
}

int	pre_here_doc(char **redirs, int i, int stdout_copy_fd, int orig_stdout)
{
	static int	quantity;

	if (!quantity)
		quantity = 0;
	if (i - 1 >= 0 && redir_type(redirs[i - 1]) == IN)
		i = here_doc(get_file_redir(redirs[i]), 0, 0, 1);
	else if (i - 1 >= 0 && (redir_type(redirs[i - 1]) == OUT || \
		redir_type(redirs[i - 1]) == APPEND))
	{
		stdout_copy_fd = dup(STDOUT_FILENO);
		if (dup2(orig_stdout, STDOUT_FILENO) < 0)
			return (-1);
		if (quantity == 0 && if_there_was_in(redirs, i) == 1)
			i = here_doc(get_file_redir(redirs[i]), 0, 0, -1);
		else
			i = here_doc(get_file_redir(redirs[i]), 0, 0, 1);
		if (dup2(stdout_copy_fd, STDOUT_FILENO) < 0)
			return (-1);
		close(stdout_copy_fd);
	}
	else
		i = pre_here_doc_2(redirs, i, quantity, orig_stdout);
	if (++quantity == get_quantity(redirs))
		quantity = 0;
	return (i);
}
