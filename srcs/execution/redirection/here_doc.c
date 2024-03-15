/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:04:09 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/16 00:16:08 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern volatile sig_atomic_t sig_pressed;

static int write_to_tmp_file(int fd, char *input)
{
    int bytes_read;
    
    input = ft_strjoin_free(input, "\n", ft_strlen("\n"));
	if (!input)
        return (-1);
	bytes_read = write(fd, input, ft_strlen(input));
	if (bytes_read < 0)
	{
        close(fd);
        return (-1);
	}
    return (0);
}

static int here_doc_loop(char *delimeter, int fd, int check_val)
{
    char *input;

	while (1)
	{
        check_val = sig_pressed;
        signal(SIGINT, new_ctrl_c);
		input = readline("heredoc> ");
		if (!input)
        {
            if (check_num(check_val, sig_pressed) == 0)
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

static void unlink_file(char *msg)
{
    if (unlink("/tmp/heredoc") < 0)
        ft_putstr_fd("Unlinking failed\n", 2);
    if (ft_strncmp(msg, "without", 7) != 0)
        ft_putstr_fd(msg, 2);
}

static int create_tmp_file(char *delimeter, int fd)
{
	fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 
        S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_putstr_fd("File creation error\n", 2);
		return (-1);
	}
    fd = here_doc_loop(delimeter, fd, 0);
	if (fd == -500)
        unlink_file("without");
	return (fd);
}

int here_doc(char *delimeter, int fd, int dup_return)
{
	fd = create_tmp_file(delimeter, 0);
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