/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_syntax_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:21:28 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/30 12:41:16 by asyvash          ###   ########.fr       */
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

static int	check_dollar_sign(char *inp, int flag, int size)
{
	static int	i;

	if (!i)
		i = -1;
	while (i++, inp[i] && i <= size)
	{
		if (inp[i] == '\'' || inp[i] == '"')
			skip_quotes(inp, &i);
		if (inp[i + 1] && (inp[i] == '>' || inp[i] == '<'))
			flag = 1;
		if (!is_whitespace(inp[i]) && inp[i] != '>' && \
			inp[i] != '<' && inp[i] != '$')
			flag = 0;
		if (inp[i] && inp[i + 1] && inp[i] == '$' && \
			!is_whitespace(inp[i + 1]) && flag == 1 \
			&& inp[i + 1] != '$')
			break ;
	}
	if (inp[i] == '\0' || i > size)
		i = -1;
	return (i);
}

static int	check_env_value(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (is_whitespace(content[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	ambiguous_redir(char *input, t_list *env)
{
	t_list	*tmp;
	int		j;

	j = 0;
	while (!is_whitespace(input[j]) && input[j])
		j++;
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(input, tmp->content, j) == 0 && \
			tmp->content[j] == '=')
		{
			if (check_env_value(tmp->content + j + 1) == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redir_syntax_checker(char *input, t_list *env)
{
	int	i;

	i = 0;
	if (quotes_validation(input))
		return (1);
	input = check_redirs(input, 0);
	if (input == NULL)
	{
		ft_putstr_fd("minishell: Error near '>' or '<'\n", 2);
		return (1);
	}
	while (1)
	{
		i = check_dollar_sign(input, 0, ft_strlen(input));
		if (i == -1)
			break ;
		if (ambiguous_redir(input + i + 1, env) == 1)
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			while (i != -1)
				i = check_dollar_sign(input, 0, ft_strlen(input));
			return (1);
		}
	}
	return (0);
}
