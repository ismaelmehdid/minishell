/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <imehdid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:21:12 by asyvash           #+#    #+#             */
/*   Updated: 2024/05/05 12:24:24 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_allocation(char *new, char **new_input)
{
	if (!new)
	{
		free_double_array(new_input);
		return (1);
	}
	return (0);
}

static char	*expand_env_var(char *input, t_list **env, char *new, int i)
{
	char	**new_input;

	new_input = split_quotes_bash(input, "", *env);
	free(input);
	if (!new_input)
		return (NULL);
	new = ft_strdup(new_input[0]);
	if (check_allocation(new, new_input) == 1)
		return (NULL);
	if (new_input[1])
	{
		i = 1;
		while (new_input[i])
		{
			new = ft_strjoin_free(new, new_input[i], \
				ft_strlen(new_input[i]));
			if (check_allocation(new, new_input) == 1)
				return (NULL);
			i++;
		}
	}
	free_double_array(new_input);
	return (new);
}

int	check_delimiter(char *delimiter, t_list **env)
{
	int	i;

	if (!env || env == NULL)
		return (1);
	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	write_to_tmp_file(int fd, char *input, t_list **env, int check_val)
{
	int	bytes_read;

	if (check_val == 0)
	{
		input = expand_env_var(input, env, NULL, 0);
		if (!input)
		{
			ft_putstr_fd("Allocation error\n", 2);
			return (1);
		}
	}
	input = ft_strjoin_free(input, "\n", ft_strlen("\n"));
	if (!input)
		return (-1);
	bytes_read = write(fd, input, ft_strlen(input));
	if (bytes_read < 0)
	{
		if (input)
			free (input);
		close(fd);
		return (-1);
	}
	free(input);
	return (0);
}

void	unlink_file(char *msg)
{
	if (unlink("/tmp/heredoc") < 0)
		ft_putstr_fd("Unlinking failed\n", 2);
	if (ft_strncmp(msg, "without", 7) != 0)
		ft_putstr_fd(msg, 2);
}
