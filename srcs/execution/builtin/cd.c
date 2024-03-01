/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:27 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/01 20:36:20 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


/*
execute_unset("OLDPWD");
find PWD, then:
char *temp = ft_strdup(env->content);
free(env->content);
env->content = ft_strdup(ft_strjoin("OLD". temp));
export(ft_strjoin("PWD", execute_pwd);
*/

int	execute_cd(char *path)
{
	char	cwd[PATH_MAX];

	path++;
	if (path[0] == '/')
	{
		if (chdir(path) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("cd");
			return (1);
		}
		if (ft_strlen(cwd) + ft_strlen(path) + 1 > PATH_MAX)
			return (1);
		ft_strlcat(cwd, "/", sizeof(cwd));
		ft_strlcat(cwd, path, sizeof(cwd));
		if (chdir(cwd) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	return (0);
}
