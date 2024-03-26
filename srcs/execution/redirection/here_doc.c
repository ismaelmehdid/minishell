/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:04:09 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/23 23:20:44 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	here_doc_loop(char *delimeter, int fd, int check_val)
{
	char	*input;

	while (1)
	{
		check_val = g_sig_pressed;
		signal(SIGINT, new_ctrl_c);
		input = readline("heredoc> ");
		if (!input)
		{
			if (check_num(check_val, g_sig_pressed) == 0)
				continue ;
			return (-500);
		}
		if (ft_strlen(input) == ft_strlen(delimeter) \
			&& ft_strnstr(input, delimeter, ft_strlen(delimeter)))
		{
			free(input);
			break ;
		}
		if (write_to_tmp_file(fd, input) == -1)
			return (-1);
	}
	return (fd);
}

static int	create_tmp_file(char *delimeter, int fd, int in_flag)
{
	fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_putstr_fd("File creation error\n", 2);
		return (-1);
	}
	if (in_flag >= 0)
	{
		in_flag = write_from_stdin_to_fd(&fd, 1, 0);
		if (in_flag < 0)
		{
			ft_putstr_fd("Error with read, write or dup2\n", 2);
			if (close(fd) < 0)
				ft_putstr_fd("File error\n", 2);
			return (-1);
		}
	}
	fd = here_doc_loop(delimeter, fd, 0);
	if (fd == -500)
		unlink_file("without");
	return (fd);
}

int	here_doc(char *delimeter, int fd, int dup_return, int in_flag)
{
	fd = create_tmp_file(delimeter, 0, in_flag);
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
