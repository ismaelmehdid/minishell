/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:27:27 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/26 23:29:01 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	backup_std(int fds[2])
{
	fds[0] = -1;
	fds[1] = -1;
	fds[0] = dup(STDIN_FILENO);
	if (fds[0] < 0)
	{
		ft_putstr_fd("STDIN dup error\n", 2);
		return (0);
	}
	fds[1] = dup(STDOUT_FILENO);
	if (fds[1] < 0)
	{
		ft_putstr_fd("STDOUT dup error\n", 2);
		close(fds[0]);
		return (0);
	}
	return (1);
}

static int	open_file_redir(char *file, t_redirection type)
{
	int	open_file;

	open_file = open(file, get_flags(type), 0664);
	if (open_file < 0)
	{
		ft_putstr_fd("Error while opening a file\n", 2);
		return (-1);
	}
	return (open_file);
}

static char	*get_file(char *rediction)
{
	int		i;
	int		j;
	char	*file;

	i = 0;
	while (rediction[i] == '>' || rediction[i] == '<'
		|| rediction[i] == ' ')
		i++;
	file = malloc(ft_strlen(rediction) - i + 1);
	if (!file)
		return (NULL);
	file[ft_strlen(rediction) - i] = '\0';
	j = 0;
	while (rediction[i] != '\0')
	{
		file[j] = rediction[i];
		i++;
		j++;
	}
	return (file);
}

static int	dup_std(t_redirection type, char *file)
{
	int	dup_return;
	int	fd;

	if (type == HERE_DOC)
		return (here_doc(file, 0, 0, -1));
	fd = open_file_redir(file, type);
	if (fd < 0)
		return (-1);
	if (type == OUT || type == APPEND)
		dup_return = dup2(fd, STDOUT_FILENO);
	else
		dup_return = dup2(fd, STDIN_FILENO);
	if (dup_return < 0)
		ft_putstr_fd("File error\n", 2);
	if (close(fd) < 0)
		ft_putstr_fd("File error\n", 2);
	return (dup_return);
}

int	make_redirection(char **redirs, int fds[2], int status, int i)
{
	char	*file;

	if (!backup_std(fds))
		return (1);
	while (redirs[i] != NULL)
	{
		file = get_file(redirs[i]);
		if (file == NULL)
		{
			ft_putstr_fd("Allocation error\n", 2);
			return (1);
		}
		if (i - 1 >= 0 && get_redir_type(redirs[i - 1]) == IN && \
			get_redir_type(redirs[i]) == HERE_DOC)
			status = here_doc(file, 0, 0, 1);
		else
			status = dup_std(get_redir_type(redirs[i]), file);
		free (file);
		if (status == -500)
			return (-500);
		if (status < 0)
			return (0);
		i++;
	}
	return (1);
}
