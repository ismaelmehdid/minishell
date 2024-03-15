/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:04:09 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/14 02:30:41 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char    *ft_strjoin_free(char *s1, char const *s2, int s2_len)
{
    int			i;
    int			j;
    char		*res;

    i = 0;
    j = ft_strlen(s1);
    res = malloc(j + s2_len + 1);
    if (!res)
    {
        free(s1);
        return (NULL);
    }
    j = 0;
    while (s1[i])
    {
        res[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        res[i + j] = s2[j];
        j++;
    }
    res[i + j] = '\0';
    free(s1);
    return (res);
}

static int here_doc_loop(char *delimeter, int fd)
{
    char *input;
    int bytes_read;

	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
            return (-500);
        if (ft_strlen(input) == ft_strlen(delimeter) \
			&& ft_strnstr(input, delimeter, ft_strlen(delimeter)))
		{
            free(input);
            break ;
        }
        input = ft_strjoin_free(input, "\n", ft_strlen("\n"));
        if (!input)
            return (-1);
		bytes_read = write(fd, input, ft_strlen(input));
		if (bytes_read < 0)
		{
        	close(fd);
        	return (-1);
		}
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
    fd = here_doc_loop(delimeter, fd);
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