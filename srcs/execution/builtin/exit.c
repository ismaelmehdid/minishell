/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:41 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/30 19:18:49 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	execute_exit(char *input, t_list **env, t_astnode *root, char **envp)
{
	char	**args;

	args = split_quotes(input, " \t\n\v\f\r", NULL);
	if (!args)
		g_last_command_status = 126;
	trim_quotes(args);
	if (!args)
		g_last_command_status = 126;
	if (size_double_array(args) > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		g_last_command_status = 1;
		return ;
	}
	if (size_double_array(args) == 1)
		g_last_command_status = ft_atoi(args[0]);
	free_double_array(args);
	free_list(env);
	free_double_array(envp);
	free_all_nodes(root);
	if (close(g_stdin_copy_fd) < 0)
		ft_putstr_fd("File error\n", 2);
	exit(g_last_command_status);
}
