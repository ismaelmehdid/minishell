/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:05 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/31 21:13:55 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int						g_stdin_copy_fd = 0;
int						g_last_command_status = 0;

int	only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	restore_stdin(int check_num)
{
	if (check_num == 1)
		printf("\033[F\033[K");
	if (!isatty(STDIN_FILENO))
	{
		if (check_num == 0)
		{
			ft_putchar_fd('\n', 2);
			printf("\033[F\033[K");
		}
		if (check_num == 3)
		{
			g_last_command_status = 130;
			ft_putchar_fd('\n', 2);
			printf("\033[F\033[K");
		}
		if (dup2(g_stdin_copy_fd, STDIN_FILENO) < 0)
		{
			ft_putstr_fd("dup2 error\n", 2);
			return (-1);
		}
		return (0);
	}
	return (2);
}

static void	minishell_loop(t_astnode *ast_root, t_list **env, char *input)
{
	while (1)
	{
		signal(SIGINT, ctrl_c);
		printf("(%d) ", g_last_command_status); // delete when finish return codes
		input = readline("BestShell😎$> ");
		if (!input && restore_stdin(3) == 0)
			continue ;
		else if (!input)
			break ;
		if (only_spaces(input) == 1)
		{
			add_history(input);
			input = check_and_modify(input, NULL, 0, 0);
			ast_root = parsing(&input, *env);
			if (ast_root)
			{
				init_executor(ast_root, env);
				free_all_nodes(ast_root);
			}
			else if (ast_root == NULL && g_last_command_status != 2 && \
				g_last_command_status != 130)
				g_last_command_status = 1;
		}
		if (input)
			free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_astnode	*ast_root;
	t_list		*env;

	ast_root = NULL;
	(void)argc;
	(void)argv;
	if (create_env(&env, envp) == 1)
	{
		ft_putstr_fd("Allocation error\n", 2);
		free_list(&env);
		return (1);
	}
	signal(SIGQUIT, SIG_IGN);
	g_stdin_copy_fd = dup(STDIN_FILENO);
	toggle_echoctl_status(-1);
	minishell_loop(ast_root, &env, NULL);
	rl_clear_history();
	toggle_echoctl_status(0);
	free_list(&env);
	close(g_stdin_copy_fd);
	return (g_last_command_status);
}
