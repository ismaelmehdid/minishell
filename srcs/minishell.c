/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:05 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/20 15:12:14 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int stdin_copy_fd = 0;

static int	create_env(t_list **env, char **envp)
{
	t_list *new_node;
	int i;

	i = 0;
    *env = NULL;
    while (envp[i] != NULL)
	{
        new_node = (t_list *)malloc(sizeof(t_list));
        if (new_node == NULL)
		{
            ft_putstr_fd("Allocation error\n", 2);
            return (1);
        }
        new_node->content = ft_strdup(envp[i]);
        if (new_node->content == NULL)
		{
            ft_putstr_fd("Allocation error\n", 2);
            return (1);
        }
        new_node->next = *env;
        *env = new_node;
		i++;
    }
	return (0);
}

int is_whitespace(char c)
{
    return (c == ' ' || (c >= 9 && c <= 13));
}

static int only_spaces(char *line)
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

static void minishell_loop(t_astnode *ast_root, t_list *env)
{
	char *input;
	
	while (1)
	{
		signal(SIGINT, ctrl_c);
		input = readline("BestShell😎$>  ");
		if (!input)
			break ;
		if (only_spaces(input) == 1)
		{
			add_history(input);
			input = check_and_modify(input, 0, 0);
			ast_root = parsing(&input);
			if (ast_root)
			{
				init_executor(ast_root, &env);
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
	stdin_copy_fd = dup(STDIN_FILENO);
	toggle_echoctl_status(-1);
	minishell_loop(ast_root, env);
	toggle_echoctl_status(0);
	free_list(&env);
	close(stdin_copy_fd);
	return (0);
}