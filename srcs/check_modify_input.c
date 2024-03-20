/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_modify_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:19:05 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/21 00:04:26 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_strnjoin(char *s1, char const *s2, int n)
{
	int			i;
	int			j;
	char		*res;

	i = -1;
	res = malloc(ft_strlen(s1) + n + 1);
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	j = -1;
	while (i++, s1[i])
		res[i] = s1[i];
	while (j++, j < n)
		res[i + j] = s2[j];
	res[i + j] = '\0';
	if (s1)
		free(s1);
	return (res);
}

static char	*check_redirs(char *inp, int i)
{
	while (inp[i] != '\0')
	{
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
				free(inp);
				return (NULL);
			}
		}
		i++;
	}
	return (inp);
}

static char	*add_tee_cmd(char *inp, char *new, int *i)
{
	if (inp[(*i)] == '>' && inp[(*i) + 1] == '>')
	{
		new = ft_strjoin_free(new, "| tee -a", 8);
		if (!new)
		{
			ft_putstr_fd("Allocation error\n", 2);
			return (NULL);
		}
		(*i) += 2;
	}
	else
	{
		new = ft_strjoin_free(new, "| tee", 5);
		if (!new)
		{
			ft_putstr_fd("Allocation error\n", 2);
			return (NULL);
		}
		(*i)++;
	}
	return (new);
}

static char	*modyfing(char *inp, char *new, int last, int i)
{
	int	j;

	while (1)
	{
		j = i;
		i = get_next_index(inp, last);
		if (i == -1)
		{
			last = get_prelast_file(inp, last);
			new = ft_strnjoin(new, inp + last, ft_strlen(inp));
			break ;
		}
		new = ft_strnjoin(new, inp + j, i - j);
		if (!new)
			break ;
		new = add_tee_cmd(inp, new, &i);
		if (!new)
			break ;
	}
	if (!new)
	{
		ft_putstr_fd("Allocation error\n", 2);
		return (NULL);
	}
	return (new);
}

char	*check_and_modify(char *input, int append, int out)
{
	char	*new;

	input = check_redirs(input, 0);
	if (input == NULL)
	{
		ft_putstr_fd("Invalid usage of '<' or '>'\n", 2);
		return (NULL);
	}
	append = count_append(input);
	out = count_out(input);
	if ((append == 0 && out == 0) || append + out == 1)
		return (input);
	new = ft_calloc(ft_strlen(input) + (append * 4) \
		+ (out * 6 - out) + 1, sizeof(char));
	if (!new)
	{
		free(input);
		ft_putstr_fd("Allocation error\n", 2);
		return (NULL);
	}
	new = modyfing(input, new, get_last_index(input), 0);
	free(input);
	if (new == NULL)
		return (NULL);
	return (new);
}
