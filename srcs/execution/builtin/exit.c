/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:41 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/23 16:31:13 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	execute_exit(char *input, t_list **env, t_astnode *root, char **envp)
{
	int	code;

	code = 0;
	while (*input && (*input >= '9' || *input <= '0'))
		input++;
	if (*input >= '0' && *input <= '9')
		code = ft_atoi(input);
	else
		code = g_last_command_status;
	free_list(env);
	free_double_array(envp);
	free_all_nodes(root);
	if (close(g_stdin_copy_fd) < 0)
		ft_putstr_fd("File error\n", 2);
	exit(code);
}
