/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:12:13 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/26 14:36:30 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path(char *cmd, char *path_full)
{
	int		i;
	char	*cmd_path;
	char	*path;
	char	**paths;

	if (!cmd || ft_strlen(cmd) == 0)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	paths = ft_split(path_full, ':');
	i = -1;
	while (paths[++i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (access(cmd_path, F_OK) == 0)
		{
			free_double_array(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_double_array(paths);
	return (NULL);
}

static void	init_redirs(t_astnode *root, char **redirections, int fds[2],
		int status)
{
	int	empty_status;

	del_redirs_from_root(&root);
	empty_status = no_cmds(root);
	status = make_redirection(redirections, fds, -1);
	if (status == -500 || empty_status == 0)
	{
		restore_std(fds);
		if (status == -500)
			ft_putchar_fd('\n', 2);
		free_double_array(redirections);
	}
	if (empty_status == 0 && g_last_command_status != 1)
		g_last_command_status = 3;
	if (status == -500 && g_last_command_status != 131)
		g_last_command_status = 130;
}

static int	execute_command(t_astnode *node, t_list **env, int fds[2])
{
	char	**envp;
	
	handle_builtin(node->value, env, node, fds);
	if (g_last_command_status != 300)
		return (0);
	envp = create_envp(*env);
	if (!envp)
	{
		ft_putstr_fd("Allocation error\n", 2);
		g_last_command_status = 1;
		return (1);
	}
	if (g_last_command_status == 300)
		g_last_command_status = 0;
	launch_executable(node->value, envp, -1);
	free_double_array(envp);
	return (0);
}

static void	simple_cmd(t_astnode *root, t_list **env,
	char **redirs, int fds[2])
{
	redirs = create_list(root);
	if (redirs)
		init_redirs(root, redirs, fds, 1);
	if (stop_exec_cmd(fds) == 0)
		return ;
	if (redirs)
		free_double_array(redirs);
	execute_command(root, env, fds);
	restore_std(fds);
}

void	init_executor(t_astnode *root, t_list **env)
{
	char		**redirections;
	int			fds[2];

	ft_memset(fds, -1, sizeof(fds));
	if (!backup_std(fds))
	{
		g_last_command_status = 1;
		return ;
	}
	g_last_command_status = 0;
	redirections = NULL;
	if (root->type == PIPE_NODE)
	{
		restore_std(fds);
		if (init_pipe(root, env, 0) == 1)
		{
			ft_putstr_fd("Error occurred\n", 2);
			g_last_command_status = 1;
		}
	}
	else if (root->type == COMMAND_NODE)
		simple_cmd(root, env, redirections, fds);
}
