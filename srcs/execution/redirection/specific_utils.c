/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specific_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:22:45 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/26 14:19:06 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	no_such_file_error(char *file)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	here_doc_exist(char **redirs, int i)
{
	int	check_val;

	check_val = 1;
	while (redirs[i])
	{
		if (ft_strncmp(redirs[i], "<<", 2) == 0)
			check_val = 0;
		i++;
	}
	return (check_val);
}

void	useless_here_doc(char **redirs, int i, int orig_stdin)
{
	close(STDIN_FILENO);
	if (dup2(orig_stdin, STDIN_FILENO))
	{
		ft_putstr_fd("dup2 error\n", 2);
		g_last_command_status = 2;
		return ;
	}
	while (redirs[i])
	{
		if (ft_strncmp(redirs[i], "<<", 2) == 0)
		{
			here_doc(get_file_redir(redirs[i]), 0, 0, orig_stdin);
			close(STDIN_FILENO);
			if (dup2(orig_stdin, STDIN_FILENO))
			{
				ft_putstr_fd("dup2 error\n", 2);
				g_last_command_status = 2;
				return ;
			}
		}
		i++;
	}
}

int	no_cmds(t_astnode *root)
{
	t_astnode	*temp;
	int			status;

	status = 1;
	del_redirs_from_root(&root);
	temp = root;
	while (temp)
	{
		if (only_spaces(temp->value) == 0
			|| (temp->left && only_spaces(temp->left->value) == 0))
			status = 0;
		temp = temp->right;
	}
	return (status);
}

int	stop_exec_cmd(int fds[2])
{
	if (g_last_command_status == 130 || \
		g_last_command_status == 3 || \
		g_last_command_status == 131)
	{
		if (g_last_command_status == 3)
			g_last_command_status = 0;
		restore_std(fds);
		return (0);
	}
	if (g_last_command_status == 350 || \
		g_last_command_status == 1)
	{
		g_last_command_status = 1;
		restore_std(fds);
		return (0);
	}
	return (1);
}
