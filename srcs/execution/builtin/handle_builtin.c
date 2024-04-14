/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/14 17:31:38 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	find_builtin_three(
	char *cmd,
	char **envp)
{
	if (get_command(cmd, "env") == 0)
	{
		return (execute_env(envp, cmd + get_cmd_args_index(cmd)));
	}
	else if (get_command(cmd, "pwd") == 0)
	{
		return (execute_pwd());
	}
	return (300);
}

static int	find_builtin_two(
	char *cmd,
	char **envp,
	t_list **env)
{
	if (get_command(cmd, "export") == 0)
	{
		return (execute_export(cmd + get_cmd_args_index(cmd), *env));
	}
	else if (get_command(cmd, "unset") == 0)
	{
		return (execute_unset(env, cmd + get_cmd_args_index(cmd)));
	}
	return (find_builtin_three(cmd, envp));
}

static int	find_builtin(
	char *cmd,
	char **envp,
	t_list **env)
{
	if (get_command(cmd, "echo") == 0)
	{
		return (execute_echo(cmd + get_cmd_args_index(cmd)));
	}
	else if (get_command(cmd, "cd") == 0)
	{
		return (execute_cd(cmd + get_cmd_args_index(cmd), env));
	}
	return (find_builtin_two(cmd, envp, env));
}

int	handle_builtin(
	char *input,
	char **envp,
	t_list **env,
	t_astnode *root)
{
	int	i;

	i = 0;
	if (!input)
		return (1);
	while (is_whitespace(input[i]))
		i++;
	input += i;
	if (get_command(input, "exit") == 0)
	{
		execute_exit(input + get_cmd_args_index(input), env, root, envp);
		return (g_last_command_status);
	}
	g_last_command_status = find_builtin(input, envp, env);
	return (g_last_command_status);
}
