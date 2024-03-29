/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:08:47 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/27 00:56:15 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*pipes_checker(char *inp, int i)
{
	if (inp[i + 1] && inp[i + 1] == '|' \
		&& inp[i + 2] && inp[i + 2] == '|')
	{
		ft_putstr_fd("parse error near `||'\n", 2);
		free(inp);
		return (NULL);
	}
	else if (inp[i + 1] && inp[i + 1] == '|')
	{
		ft_putstr_fd("parse error near `|'\n", 2);
		free(inp);
		return (NULL);
	}
	if (inp[i + 1] != '\0')
	{
		if (check_for_spaces(inp + i + 1) == 1)
		{
			free(inp);
			ft_putstr_fd("parse error near `|'\n", 2);
			return (NULL);
		}
	}
	return (inp);
}

static char	*pipes_format_checker(char *inp)
{
	int	i;

	i = 0;
	while (inp[i] && (inp[i] == ' ' || (inp[i] >= 9 && inp[i] <= 13)))
		i++;
	if (inp[i] == '|')
	{
		if (inp[i + 1] && inp[i + 1] == '|')
			ft_putstr_fd("parse error near `||'\n", 2);
		else
			ft_putstr_fd("parse error near `|'\n", 2);
		free(inp);
		return (NULL);
	}
	while (inp[i])
	{
		while (inp[i] && inp[i] != '|')
			i++;
		if (inp[i] && !pipes_checker(inp, i))
			return (NULL);
		if (inp[i])
			i++;
	}
	return (inp);
}

static char	*set_new_command(char *input, int i)
{
	char		*new_inp;
	char		*cmd;

	cmd = readline("pipe> ");
	if (!cmd)
	{
		free(input);
		g_sig_pressed++;
		return (NULL);
	}
	while (cmd[i] && (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13)))
		i++;
	new_inp = ft_strjoin_free(input, cmd, ft_strlen(cmd));
	if (!new_inp)
	{
		free(input);
		free(cmd);
		return (NULL);
	}
	free(cmd);
	return (new_inp);
}

static char	*validation_loop(char *input, char *backup, int num)
{
	while (input && check_last_pipe_command(input))
	{
		backup = get_backup(backup, input);
		if (!backup)
			return (NULL);
		num = g_sig_pressed;
		input = set_new_command(input, 0);
		if (!input && num >= g_sig_pressed)
		{
			dup2(g_stdin_copy_fd, STDIN_FILENO);
			return (NULL);
		}
		else if (input && !pipes_format_checker(input))
			return (NULL);
		else if (!input && check_num(num + 1, g_sig_pressed) == 0)
		{
			input = ft_strdup(backup);
			if (!input)
				return (NULL);
			continue ;
		}
		if (input)
			input = pipes_format_checker(input);
	}
	return (input);
}

char	*pipes_validation(char *input)
{
	char	*backup;

	backup = NULL;
	input = pipes_format_checker(input);
	if (!input)
	{
		g_last_command_status = 2;
		return (NULL);
	}
	signal(SIGINT, new_ctrl_c_pipe);
	input = validation_loop(input, backup, 0);
	if (backup)
		free(backup);
	if (!input || input == NULL)
	{
		if (g_last_command_status != 130)
			g_last_command_status = 2;
		return (NULL);
	}
	return (input);
}
