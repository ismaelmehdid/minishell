/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:32 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/15 04:04:27 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	length_until_equal(char *str)
{
	int	length;

	length = 0;
	while (str[length] && str[length] != '=')
		length++;
	return (length);
}

static int	search_and_print_env(char *env_found, t_list **env)
{
	t_list	*temp;
	int		i;

	temp = *env;
	i = 0;
	if (ft_strcmp(env_found, "?"))
	{
		ft_putnbr_fd(last_command_status, STDOUT_FILENO);
		return (0);
	}
	while (temp)
	{
		if (length_until_equal(temp->content) == ft_strlen(env_found)
			&& strncmp(temp->content, env_found, ft_strlen(env_found)) == 0)
		{
			while (temp->content[i] && temp->content[i] != '=')
				i++;
			if (temp->content[i] == '=')
				i++;
			ft_putstr_fd(temp->content + i, STDOUT_FILENO);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

static void	env_printing(char *arg, t_astnode *root, t_list **env, int *i)
{
	char	env_found[1024];
	int		j;
	int		quote;

	ft_bzero(env_found, sizeof(env_found));
	j = 0;
	if (arg[(*i) + 1] == ' ' || (arg[(*i) + 1] >= 9 && arg[(*i) + 1] <= 13))
	{
		ft_putchar_fd(arg[*i], STDOUT_FILENO);
		return ;
	}
	(*i)++;
	quote = root->quotes_indexes[root->starting_index + *i];
	while (arg[*i] && (root->quotes_indexes[root->starting_index + *i] == quote)
		&& arg[*i] != ' ' && arg[*i] != '\'' && arg[*i] != '"'
		&& (arg[*i] < 9 || arg[*i] > 13) && arg[*i] != '=')
	{
		env_found[j] = arg[*i];
		j++;
		(*i)++;
	}
	search_and_print_env(env_found, env);
}

static int	print_arg(char *arg, int option, t_astnode *root, t_list **env)
{
	int	i;

	i = 0;
	while (*arg == ' ' || (*arg >= 9 && *arg <= 13))
	{
		arg++;
		root->starting_index++;
	}
	while (arg[i] != '\0')
	{
		if (arg[i] == '$'
			&& root->quotes_indexes[root->starting_index + i] != 1)
			env_printing(arg, root, env, &i);
		if ((arg[i] == '\'' && !(root->quotes_indexes[root->starting_index + i]))
			|| (arg[i] == '"' && root->quotes_indexes[root->starting_index + i] == 0))
		{
			i++;
			continue ;
		}
		ft_putchar_fd(arg[i], STDOUT_FILENO);
		if (arg[i])
			i++;
	}
	if (option)
		return (0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

static bool	check_option(char **arg, t_astnode *root)
{
	int	i;

	i = 0;
	if (arg[0][i] && arg[0][i + 1] && arg[0][i] == '-'
		&& arg[0][i + 1] == 'n')
	{
		i++;
		while (arg[0][i] == 'n')
			i++;
		if (arg[0][i] != ' ' || (arg[0][i] >= 9 && arg[0][i] <= 13))
			return (false);
		root->starting_index += i;
		*arg = *arg + i;
		return (true);
	}
	return (false);
}

int	execute_echo(char *arg, t_astnode *root, t_list **env)
{
	bool	option;

	option = true;
	while (*arg == ' ' || (*arg >= 9 && *arg <= 13))
	{
		arg++;
		root->starting_index++;
	}
	if (*arg == '\0')
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	option = check_option(&arg, root);
	print_arg(arg, option, root, env);
	return (0);
}
