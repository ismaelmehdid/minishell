/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:56:03 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/01 18:58:39 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_env_var_value(char *env)
{
	while (*env && *env != '=')
		env++;
	if (*env == '=')
		env++;
	return (env);
}

static int	handle_special_unix_variable(
	char *result,
	t_cpy_word_indexes *indexes,
	char *env_var_name)
{
	char	*code;

	code = NULL;
	if (ft_strncmp(env_var_name, "?", ft_strlen(env_var_name)) == 0)
	{
		code = ft_itoa(g_last_command_status);
		ft_strlcpy(result + indexes->k, code, ft_strlen(code) + sizeof(char));
		indexes->i += (ft_strlen(env_var_name) + sizeof(char));
		indexes->k += (ft_strlen(code));
		free(code);
		return (0);
	}
	return (1);
}

void	add_env_value(
	char *result,
	char *input,
	t_cpy_word_indexes *indexes,
	t_list *env)
{
	char	env_var_name[NAME_MAX];
	t_list	*temp;

	get_variable_name(input, indexes->i, env_var_name);
	if (handle_special_unix_variable(result, indexes, env_var_name) == 0)
		return ;
	temp = env;
	while (temp)
	{
		if (env_var_name_size(temp->content) == ft_strlen(env_var_name)
			&& !ft_strncmp(temp->content, env_var_name,
				env_var_name_size(temp->content)))
		{
			ft_strlcpy(result + indexes->k,
				get_env_var_value(temp->content),
				ft_strlen(get_env_var_value(temp->content)) + sizeof(char));
			indexes->i += (ft_strlen(env_var_name) + sizeof(char));
			indexes->k += (ft_strlen(get_env_var_value(temp->content)));
			return ;
		}
		temp = temp->next;
	}
	indexes->i += (ft_strlen(env_var_name) + sizeof(char));
}
