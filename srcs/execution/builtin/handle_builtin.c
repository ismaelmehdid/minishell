/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/05 20:05:22 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int check_cmd(char *cmd, int end)
{
	if (cmd[end] != ' ' && ft_strlen(cmd) != end)
	{
		not_found(cmd);
		return (1);
	}
	return (0);
}

/*static char	*unset_if_exist(t_list *env, char *key)
{
	int	i;
	int	j;
	char	*new_key;
	t_list	*cur;

	i = 0;
	while (key[i] != '\0' && key[i] != '=')
		i++;
	new_key = malloc(i + 1);
	if (!new_key)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_key[j] = key[j];
		j++;
	}
	new_key[j] = '\0';
	j = 0;
	while (new_key[j] == ' ')
		j++;
	cur = env;
	while (cur != NULL && ft_strncmp(cur->content, new_key + j, ft_strlen(new_key) - j) != 0)
        cur = cur->next;
    if (cur == NULL)
	{
		free(new_key);
		return (NULL);
	}
	return (new_key);
}*/

static int find_builtin_two(char *cmd, char **envp, t_list **env)
{
	//char	*key;

	if (ft_strncmp(cmd, "export", 6) == 0) // check for correct arg, unset if exist
	{
		if (check_cmd(cmd, 6) == 1)
			return (127);
		//key = unset_if_exist(env, cmd + 6);
		//if (key != NULL)
		//	execute_unset(&env, key);
		//free(key);
		return (execute_export(cmd + 6, *env, envp));
	}
	else if (ft_strncmp(cmd, "unset", 5) == 0) // seg fault if firt elem
	{
		if (check_cmd(cmd, 5) == 1)
			return (127);
		return (execute_unset(env, cmd + 5));
	}
	else if (ft_strncmp(cmd, "env", 3) == 0)
	{
		if (check_cmd(cmd, 3) == 1)
			return (127);
		return (execute_env(envp));
	}
	return (1);
}

static int find_builtin(char *cmd, char **envp, t_list **env)
{
	if (ft_strncmp(cmd, "echo", 4) == 0) // quotes isn't implemented, env variables, for example echo $PATH
	{
		if (check_cmd(cmd, 4) == 1)
			return (127);
		return (execute_echo(cmd + 4));
	}
	else if (ft_strncmp(cmd, "cd", 2) == 0) // something wrong + OLDPWD, PWD, HOME
	{
		if (check_cmd(cmd, 2) == 1)
			return (127);
		return (execute_cd(cmd + 2, env));
	}
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
	{
		if (check_cmd(cmd, 3) == 1)
			return (127);
		return (execute_pwd());
	}
	return (find_builtin_two(cmd, envp, env));
}

int	handle_builtin(char *input, char **envp, t_list **env, t_astnode *root)
{
	int i;

	i = 0;
	if (!input)
		return (1);
	while (input[i] && (input[i] == 32 || (input[i] >= 9 && input[i] <= 13)))
		i++;
	if (ft_strncmp(input + i, "exit", 4) == 0) // soon
	{
		if (check_cmd(input + i, 4) == 1)
			return (127);
		execute_exit(input, env, root, envp);
	}
	return (find_builtin(input + i, envp, env));
}