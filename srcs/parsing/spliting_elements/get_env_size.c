/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:56:06 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/26 14:37:04 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	env_var_name_size(char *env_var)
{
	int	length;

	length = 0;
	while (env_var[length] && env_var[length] != '=')
		length++;
	return (length);
}

static int	env_var_value_size(char *env_var)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	if (env_var[i] == '=')
		i++;
	while (env_var[i])
	{
		length++;
		i++;
	}
	return (length);
}

int	get_variable_name(char *input, int i, char *dest)
{
	int	j;

	j = 0;
	if (input[i] == '$')
		i++;
	while (input[i] && !is_whitespace(input[i]) && input[i]
		!= '"' && input[i] != '\'')
	{
		dest[j] = input[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (j);
}

int	search_env_size(char *input, int *i, t_list *env)
{
	char	env_var_name[NAME_MAX];
	t_list	*temp;
	int		input_var_size;

	input_var_size = get_variable_name(input, *i, env_var_name);
	if (ft_strncmp(env_var_name, "?", input_var_size) == 0)
	{
		*i += (input_var_size + sizeof(char));
		return (ft_strlen(ft_itoa(g_last_command_status)));
	}
	temp = env;
	while (temp)
	{
		if (env_var_name_size(temp->content) == input_var_size)
		{
			if (ft_strncmp(temp->content, env_var_name, env_var_name_size(temp->content)) == 0)
			{
				*i += (input_var_size + sizeof(char));
				return (env_var_value_size(temp->content));
			}
		}
		temp = temp->next;
	}
	*i += (input_var_size + sizeof(char));
	return (0);
}