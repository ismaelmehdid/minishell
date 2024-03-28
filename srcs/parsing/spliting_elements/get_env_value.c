/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:56:03 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/27 22:52:27 by imehdid          ###   ########.fr       */
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

void	add_env_value(char *result, char *input, int *i, int *k, t_list *env)
{
	char	env_var_name[NAME_MAX];
	t_list	*temp;
	char	*code;
	
	code = NULL;
	get_variable_name(input, *i, env_var_name);
	if (ft_strncmp(env_var_name, "?", ft_strlen(env_var_name)) == 0)
	{
		code = ft_itoa(g_last_command_status);
		ft_strlcpy(result + *k, code, ft_strlen(code) + sizeof(char));
		*i += (ft_strlen(env_var_name) + sizeof(char));
		*k +=  (ft_strlen(code) + sizeof(char));
		free(code);
		return ;
	}
	temp = env;
	while (temp)
	{
		if (env_var_name_size(temp->content) == ft_strlen(env_var_name))
		{
			if (ft_strncmp(temp->content, env_var_name, env_var_name_size(temp->content)) == 0)
			{
				ft_strlcpy(result + *k, get_env_var_value(temp->content), ft_strlen(get_env_var_value(temp->content)) + sizeof(char));
				*i += (ft_strlen(env_var_name) + sizeof(char));
				*k +=  (ft_strlen(get_env_var_value(temp->content)));
				return ;
			}
		}
		temp = temp->next;
	}
	*i += (ft_strlen(env_var_name) + sizeof(char));
}