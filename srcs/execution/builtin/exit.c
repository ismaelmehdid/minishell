/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <imehdid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:41 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/11 15:44:47 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_args_quantity(char **args)
{
	if (size_double_array(args) > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_last_command_status = 1;
		free_double_array(args);
		return (1);
	}
	return (0);
}

static int	check_all_digits(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[j])
	{
		while (args[j][i])
		{
			if (!ft_isdigit(args[j][i]))
			{
				ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
				ft_putstr_fd(args[j], STDERR_FILENO);
				ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
				g_last_command_status = 2;
				free_double_array(args);
				return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

static int	errors_handler(char **args)
{
	if (check_all_digits(args))
		return (1);
	if (check_args_quantity(args))
		return (1);
	return (0);
}

void	execute_exit(char *input, t_list **env, t_astnode *root, char **envp)
{
	char	**args;

	args = split_quotes(input, " \t\n\v\f\r", NULL);
	if (!args)
		g_last_command_status = 126;
	trim_quotes(args);
	if (!args)
		g_last_command_status = 126;
	if (errors_handler(args))
		return ;
	if (size_double_array(args) == 1)
		g_last_command_status = ft_atoi(args[0]);
	free_double_array(args);
	free_list(env);
	free_double_array(envp);
	free_all_nodes(root);
	if (close(g_stdin_copy_fd) < 0)
		ft_putstr_fd("File error\n", 2);
	exit(g_last_command_status);
}
