/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 00:04:18 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/20 17:42:11 by imehdid          ###   ########.fr       */
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
	while (inp[i] && (inp[i] == ' ' || (inp[i] >= 9 && inp[i] <= 13)))
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
