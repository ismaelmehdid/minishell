/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/23 16:19:13 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	find_builtin_three(char *cmd, char **envp, t_astnode *root)
{
	if (get_command(cmd, "env", root) == 0)
	{
		return (execute_env(envp));
	}
	else if (get_command(cmd, "pwd", root) == 0)
	{
		return (execute_pwd());
	}
	return (300);
}

static int	find_builtin_two(char *cmd, char **envp, t_list **env, t_astnode *root)
{
	if (get_command(cmd, "export", root) == 0)
	{
		return (execute_export(cmd + get_command_args_indexes(cmd, root), *env, envp));
	}
	else if (get_command(cmd, "unset", root) == 0)
	{
		return (execute_unset(env, cmd + get_command_args_indexes(cmd, root)));
	}
	return (find_builtin_three(cmd, envp, root));
}

static int	find_builtin(char *cmd, char **envp, t_list **env, t_astnode *root)
{
	int	args_index;

	args_index = 0;
	if (get_command(cmd, "echo", root) == 0)
	{
		args_index = get_command_args_indexes(cmd, root);
		root->starting_index = args_index;
		return (execute_echo(cmd + args_index, root, env));
	}
	else if (get_command(cmd, "cd", root) == 0)
	{
		return (execute_cd(cmd + get_command_args_indexes(cmd, root), env));
	}
	return (find_builtin_two(cmd, envp, env, root));
}

int	handle_builtin(char *input, char **envp, t_list **env, t_astnode *root)
{
	int	i;

	i = 0;
	if (!input)
		return (1);
	while (input[i] && (input[i] == 32 || (input[i] >= 9 && input[i] <= 13)))
		i++;
	root->starting_index = i;
	input += i;
	if (get_command(input, "exit", root) == 0)
	{
		execute_exit(input + get_command_args_indexes(input, root), env, root, envp);
	}
	g_last_command_status = find_builtin(input + i, envp, env, root);
	return (g_last_command_status);
}
