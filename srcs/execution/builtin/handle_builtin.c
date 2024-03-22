/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/22 18:42:28 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_cmd(char *cmd, int end)
{
	if (cmd[end] != ' ' && ft_strlen(cmd) != end)
	{
		not_found(cmd);
		return (1);
	}
	return (0);
}

static int	find_builtin_three(char *cmd, char **envp)
{
	if (ft_strncmp(cmd, "env", 3) == 0)
	{
		if (check_cmd(cmd, 3) == 1)
			return (127);
		return (execute_env(envp));
	}
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
	{
		if (check_cmd(cmd, 3) == 1)
			return (127);
		return (execute_pwd());
	}
	return (300);
}

static int	find_builtin_two(char *cmd, char **envp, t_list **env)
{
	if (ft_strncmp(cmd, "export", 6) == 0)
	{
		if (check_cmd(cmd, 6) == 1)
			return (127);
		return (execute_export(cmd + 6, *env, envp));
	}
	else if (ft_strncmp(cmd, "unset", 5) == 0)
	{
		if (check_cmd(cmd, 5) == 1)
			return (127);
		return (execute_unset(env, cmd + 5));
	}
	return (find_builtin_three(cmd, envp));
}

static int	find_builtin(char *cmd, char **envp, t_list **env, t_astnode *root)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
	{
		if (check_cmd(cmd, 4) == 1)
			return (127);
		root->starting_index += 4;
		return (execute_echo(cmd + 4, root, env));
	}
	else if (ft_strncmp(cmd, "cd", 2) == 0)
	{
		if (check_cmd(cmd, 2) == 1)
			return (127);
		return (execute_cd(cmd + 2, env));
	}
	return (find_builtin_two(cmd, envp, env));
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
	if (ft_strncmp(input + i, "exit", 4) == 0)
	{
		if (check_cmd(input + i, 4) == 1)
		{
			g_last_command_status = 127;
			return (g_last_command_status);
		}
		execute_exit(input, env, root, envp);
	}
	g_last_command_status = find_builtin(input + i, envp, env, root);
	return (g_last_command_status);
}
