/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:56:06 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/27 22:36:32 by imehdid          ###   ########.fr       */
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

static int	compare_env_name(char *content, int *i, int var_size, char *var_name)
{
	if (env_var_name_size(content) == var_size)
	{
		if (ft_strncmp(content, var_name, env_var_name_size(content)) == 0)
		{
			*i += (var_size + sizeof(char));
			return (env_var_value_size(content));
		}
	}
	return (-1);
}

int	search_env_size(char *input, int *i, t_list *env)
{
	char	env_var_name[NAME_MAX];
	t_list	*temp;
	int		input_var_size;
	int		res;

	res = 0;
	input_var_size = get_variable_name(input, *i, env_var_name);
	if (ft_strncmp(env_var_name, "?", input_var_size) == 0)
	{
		*i += (input_var_size + sizeof(char));
		return (ft_strlen(ft_itoa(g_last_command_status)));
	}
	temp = env;
	while (temp)
	{
		res = compare_env_name(temp->content, i, input_var_size, env_var_name);
		if (res != -1)
			return (res);
		temp = temp->next;
	}
	*i += (input_var_size + sizeof(char));
	return (0);
}