/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_syntax_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:21:28 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/15 13:32:21 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*check_redirs(char *inp, int i)
{
	while (i < ft_strlen(inp))
	{
		if (inp[i] == '\'' || inp[i] == '"')
			skip_quotes(inp, &i);
		if (inp[i] == '>' || inp[i] == '<')
		{
			if (inp[i] == '>' && inp[i + 1] == '>')
				i += 2;
			else if (inp[i] == '<' && inp[i + 1 == '<'])
				i += 2;
			else
				i++;
			while (is_whitespace(inp[i]))
				i++;
			if (inp[i] == '\0' || inp[i] == '<' || \
				inp[i] == '>' || inp[i] == '|')
			{
				g_last_command_status = 2;
				return (NULL);
			}
		}
		i++;
	}
	return (inp);
}

int	redir_syntax_checker(char *input)
{
	if (quotes_validation(input))
		return (1);
	input = check_redirs(input, 0);
	if (input == NULL)
	{
		ft_putstr_fd("Invalid usage of '<' or '>'\n", 2);
		return (1);
	}
	return (0);
}
