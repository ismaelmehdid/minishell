/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:05 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/23 16:26:14 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int						g_stdin_copy_fd = 0;
int						g_last_command_status = 0;
volatile sig_atomic_t	g_sig_pressed = 0;

int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

void	print_prompt(int status)
{
	printf("BestShell😎");
	if (status != 0)
	{
		printf("\x1b[31m");
    	printf("(%d)", status);
    	printf("\x1b[0m");
	}
	else
	{
		printf("\x1b[32m");
    	printf("(%d)", status);
    	printf("\x1b[0m");
	}
	printf(" $> ");
}

static void	minishell_loop(t_astnode *ast_root, t_list **env)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, ctrl_c);
		print_prompt(g_last_command_status);
		input = readline("");
		if (!input)
			break ;
		if (only_spaces(input) == 1)
		{
			add_history(input);
			input = check_and_modify(input, 0, 0);
			ast_root = parsing(&input);
			if (ast_root)
			{
				init_executor(ast_root, env);
				free_all_nodes(ast_root);
			}
		}
		if (input)
			free(input);
	}
	rl_clear_history();
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
	minishell_loop(ast_root, &env);
	toggle_echoctl_status(0);
	free_list(&env);
	close(g_stdin_copy_fd);
	return (0);
}
