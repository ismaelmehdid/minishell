/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:05 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/27 17:52:19 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int						g_last_command_status = 0;

static void	minishell(t_astnode *root, t_list **env, char *input)
{
	add_history(input);
	root = parsing(&input, *env);
	if (root)
	{
		init_executor(root, env);
		free_all_nodes(root);
	}
	else if (root == NULL && g_last_command_status != 2 && \
		g_last_command_status != 130 && \
		g_last_command_status != 131)
		g_last_command_status = 1;
}

static int	prompt_loop(t_astnode *root, t_list **env,
			char *input, int orig_stdin)
{
	while (1)
	{
		orig_stdin = dup(STDIN_FILENO);
		if (orig_stdin < 0)
			return (1);
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		input = readline("BestShell😎$> ");
		if (!input && restore_stdin(3, orig_stdin) == 0)
		{
			close(orig_stdin);
			continue ;
		}
		else if (!input)
		{
			close (orig_stdin);
			break ;
		}
		close(orig_stdin);
		if (only_spaces(input) == 1)
			minishell(root, env, input);
		if (input)
			free(input);
	}
	return (g_last_command_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_astnode	*root;
	t_list		*env;

	root = NULL;
	(void)argc;
	(void)argv;
	if (create_env(&env, envp) == 1)
	{
		ft_putstr_fd("Allocation error\n", 2);
		free_list(&env);
		return (1);
	}
	g_last_command_status = prompt_loop(root, &env, NULL, 0);
	ft_putstr_fd("exit\n", 2);
	rl_clear_history();
	free_list(&env);
	return (g_last_command_status);
}
