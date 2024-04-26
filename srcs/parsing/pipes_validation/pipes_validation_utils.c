/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 00:04:18 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/26 15:03:24 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_backup(char *backup, char *input)
{
	if (backup)
		free(backup);
	backup = ft_strdup(input);
	if (!backup)
	{
		free(input);
		ft_putstr_fd("Allocation error\n", 2);
		return (NULL);
	}
	return (backup);
}

int	check_for_spaces(char *inp)
{
	int	i;

	i = 0;
	while (is_whitespace(inp[i]))
		i++;
	if (i > 0 && inp[i] == '|')
		return (1);
	return (0);
}

int	check_last_pipe_command(char *inp)
{
	int	i;

	i = ft_strlen(inp) - 1;
	while (i >= 0 && (inp[i] == ' ' \
		|| (inp[i] >= 9 && inp[i] <= 13)))
		i--;
	if (i >= 0 && inp[i] == '|')
		return (1);
	return (0);
}

char	*print_parse_error(char *input, int i)
{
	if (input[i + 1] && input[i + 1] == '|')
		ft_putstr_fd("parse error near `||'\n", 2);
	else
		ft_putstr_fd("parse error near `|'\n", 2);
	free(input);
	return (NULL);
}

void	exit_program(char *backup, t_list **env)
{
	free(backup);
	free_list(env);
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putstr_fd("unexpected end of file\n", 2);
	ft_putstr_fd("exit\n", 2);
	exit (2);
}
