/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:22:13 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/28 17:50:06 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int  check_exit_args_in_pipes(char *input)
{
	char	**args;
	int		code;

	code = 0;
	args = split_quotes_bash(input, " \t\n", NULL);
	if (!args)
		g_last_command_status = 126;
	trim_quotes(args);
	if (!args)
		g_last_command_status = 126;
	code = errors_handler(args);
	return (code);
}

static void exec_in_child(t_pipeline *utl, t_list **env, t_astnode *root)
{
	char    **envp;
	int		i;

	i = 0;
	while (is_whitespace(utl->cmds[utl->k][i]))
		i++;
	utl->cmds[utl->k] += i;
	if (get_command(utl->cmds[utl->k], "exit") == 0)
	{
		if (check_exit_args_in_pipes(utl->cmds[utl->k] + \
			get_cmd_args_index(utl->cmds[utl->k])) != 2)
			free_pipeline_util(utl);
	}
	g_last_command_status = 
		handle_builtin(utl->cmds[utl->k], env, root, utl->fds);
	if (g_last_command_status != 300)
	{
		free_child_if_builtin(utl, env, root);
		exit(g_last_command_status);
	}
	envp = create_envp(*env);
	close(utl->fds[0]);
	close(utl->fds[1]);
	launch_cmd(utl->cmds[utl->k], envp, NULL, NULL);
}

static void	handle_redir(t_pipeline *utl)
{
	char	**redirs;
	int		status;
	int		empty_status;

	redirs = ft_split(utl->redirs[utl->k], '\t');
	if (!redirs)
	{
		free_pipeline_util(utl);
		exit (1);
	}
	empty_status = check_empty_status(utl->cmds[utl->k]);
	status = make_redirection(redirs, utl->fds, -1);
	free_double_array(redirs);
	if (status == -500 || empty_status == 0)
	{
		restore_std(utl->fds);
		if (status == -500)
			ft_putchar_fd('\n', 2);
	}
	if (empty_status == 0 && g_last_command_status != 1)
		g_last_command_status = 3;
	else if (status == -500)
		g_last_command_status = 130;
	stop_exec(utl);
}

void	child_process(t_pipeline *utl, t_list **env, t_astnode *root)
{
	if (handle_fds_dup(utl->cmds, utl) != 0)
	{
		free_pipeline_util(utl);
		exit (1);
	}
	if (utl->redirs[utl->k] && (utl->redirs[utl->k][0] == '<' || \
		utl->redirs[utl->k][0] == '>'))
		handle_redir(utl);
	while (utl->m < 2 * utl->i)
	{
		close(utl->fd[utl->m]);
		utl->m++;
	}
	exec_in_child(utl, env, root);
}