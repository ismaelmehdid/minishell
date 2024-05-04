/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:21:12 by asyvash           #+#    #+#             */
/*   Updated: 2024/05/04 02:45:12 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*expand_env_var(char *input, t_list **env);

static int	get_env_indx(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]) || str[i] == '$')
			break ;
		i++;
	}
	return (i);
}

static char	*set_new_input(char *input, char *env_var, int i, t_list **env)
{
	int		j;
	char	*new;

	new = malloc(ft_strlen(input) + 1);
	if (!new)
	{
		free(input);
		return (NULL);
	}
	//printf("input = %s\nenv_var = %s\n", input, env_var);
	ft_strlcpy(new, input, i);
	j = 0;
	while (!ft_isdigit(env_var[0]) && env[j] && env_var[j] != '=')
		j++;
	if (env_var[j] == '=')
		j++;
	if (env_var[j] == '\0')
		new = ft_strjoin_free(new, "\0", 1);
	else
		new = ft_strjoin_free(new, env_var + j, ft_strlen(env_var + j));
	while(input[i] && !is_whitespace(input[i]) && input[i] != '$')
		i++;
	if (input[i] == '\0')
		new = ft_strjoin_free(new, "\0", 1);
	else
		new = ft_strjoin_free(new, input + i, ft_strlen(input + i));
	free(input);
	return (expand_env_var(new, env));
}

char	*expand_env_var(char *input, t_list **env)
{
	t_list	*tmp;
	int		i;
	int		j;
	
	if (!input)
		return (NULL);
	i = 0;
	tmp = *env;
	while (input[i] && input[i + 1] && input[i] != '$')
		i++;
	if (input[i] == '\0' && !input[i + 1])
		return (input);
	if (input[i] == '$' && input[i + 1] == '?')
		return (set_new_input(input, ft_itoa(g_last_command_status), i, env));
	if (input[i] == '$' && input[i + 1] != '\0')
	{
		j = get_env_indx(input + i + 1);
		while (tmp)
		{
			if (tmp->content[j] && tmp->content[j] == '=' && \
				ft_strncmp(input + i + 1, tmp->content, j) == 0)
				return (set_new_input(input, tmp->content, i + 1, env));
			tmp = tmp->next;
		}
		return (set_new_input(input, "\0", i + 1, env));
	}
	return (input);
}

static int	check_delimiter(char *delimiter, t_list **env)
{
	int	i;

	if (!env || env == NULL)
		return (1);
	i = 0;
	if (delimiter[i] == '"')
		skip_quotes(delimiter, &i);
	if (delimiter[i] == '\0')
		return (1);
	return (0);
}

int	write_to_tmp_file(int fd, char *input, t_list **env, char *delimiter)
{
	int	bytes_read;

	if (check_delimiter(delimiter, env) == 0)
	{
		input = expand_env_var(input, env);
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
