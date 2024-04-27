/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:41 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/25 19:03:27 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_args_quantity(char **args)
{
	if (size_double_array(args) > 1)
	{
		write (STDERR_FILENO, "exit\n", 6);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_last_command_status = 1;
		return (1);
	}
	return (0);
}

static int	check_all_digits(char *args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		if (!ft_isdigit(args[i]))
		{
			if (i == 0 && args[i] == '-')
			{
				i++;
				continue ;
			}
			write (STDERR_FILENO, "exit\n", 6);
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			g_last_command_status = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	errors_handler(char **args)
{
	if (check_all_digits(args[0]))
		return (1);
	if (check_args_quantity(args))
	{
		free_double_array(args);
		return (2);
	}
	return (0);
}

void	execute_exit(char *input, t_list **env, t_astnode *root, char **envp)
{
	char	**args;
	int		code;

	code = 0;
	args = split_quotes(input, " \t\n\v\f\r", NULL);
	if (!args)
		g_last_command_status = 126;
	trim_quotes(args);
	if (!args)
		g_last_command_status = 126;
	code = errors_handler(args);
	if (code == 2)
		return ;
	if (code == 0 && size_double_array(args) == 1)
		g_last_command_status = ft_atoi(args[0]);
	free_double_array(args);
	free_list(env);
	rl_clear_history();
	free_double_array(envp);
	free_all_nodes(root);
	if (close(g_stdin_copy_fd) < 0)
		ft_putstr_fd("File error\n", 2);
	if (code == 0)
		write (STDOUT_FILENO, "exit\n", 6);
	exit(g_last_command_status);
}
