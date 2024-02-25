/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:31:31 by asyvash           #+#    #+#             */
/*   Updated: 2024/02/25 13:32:41 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

typedef struct s_pipeline
{
    int i;
	int j;
	int k;
	int m;
	pid_t pid;
	int *fd;
	char *path;;
	char **path_env;
}              t_pipeline;

#endif