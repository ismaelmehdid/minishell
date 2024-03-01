/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:05 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/01 20:51:22 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tree(t_astnode *root)
{
	if (!root)
		return ;
	printf ("Type: %d, Value: %s\n", root->type, root->value);
	print_tree (root->left);
	print_tree (root->right);
}

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

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_astnode	*ast_root;
	t_list	*env;

	ast_root = NULL;
	(void)argc;
	(void)argv;
	if (create_env(&env, envp) == 1)
	{
		ft_putstr_fd("Env malloc allocationg error\n", 2);
		free_list(&env);
		return (1);
	}
	handle_signals();
	while (1)
	{
		input = readline("BestShell😎$>  ");
		if (!input)
			return (1);
		add_history(input);
		ast_root = parsing(&input);
		if (input)
			free(input);
		if (ast_root)
		{
			print_tree(ast_root);
			if (init_executor(ast_root, env) == 1)
			{
				free_all_nodes(ast_root);
				free_list(&env);
				program_exit(1);
			}
			free_all_nodes(ast_root);
		}
	}
	free_list(&env);
	return (0);
}