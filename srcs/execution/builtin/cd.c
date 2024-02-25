/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:37:27 by asyvash           #+#    #+#             */
/*   Updated: 2024/02/25 15:39:49 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int execute_cd(char *path)
{
    char cwd[PATH_MAX];

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