/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:05 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/15 04:09:47 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*void	print_tree(t_astnode *root)
{
	int	i;

	i = 0;
	if (!root)
		return ;
	printf ("Type: %d, Value: %s\n", root->type, root->value);
	if (root->type == COMMAND_NODE)
	{
		while (i < ft_strlen(root->value))
		{
			printf ("%d, ", root->quotes_indexes[i]);
			i++;
		}
	}
	print_tree (root->left);
	print_tree (root->right);
}*/

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
            ft_putstr_fd("Memory allocation failed\n", 2);
            return (1);
        }
        new_node->content = ft_strdup(envp[i]);
        if (new_node->content == NULL)
		{
            ft_putstr_fd("ft_strdup failed", 2);
            return (1);
        }
        new_node->next = *env;
        *env = new_node;
		i++;
    }
	return (0);
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

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_astnode	*ast_root;
	t_list		*env;

	ast_root = NULL;
	(void)argc;
	(void)argv;
	if (create_env(&env, envp) == 1)
	{
		ft_putstr_fd("Env malloc allocationg error\n", 2);
		free_list(&env);
		return (1);
	}
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, ctrl_c);
		toggle_echoctl_status(-1);
		input = readline("BestShell😎$>  ");
		if (!input)
		{
			toggle_echoctl_status(0);
			break ;
		}
		if (only_spaces(input) == 1)
		{
			add_history(input);
			ast_root = parsing(&input);
			if (ast_root)
			{
				init_executor(ast_root, &env);
				free_all_nodes(ast_root);
			}
		}
		free(input);
	}
	rl_clear_history();
	free_list(&env);
	return (0);
}