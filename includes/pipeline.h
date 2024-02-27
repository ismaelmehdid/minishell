/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:31:31 by asyvash           #+#    #+#             */
/*   Updated: 2024/02/27 23:16:43 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

typedef struct s_pipeline
{
	int			i;
	int			j;
	int			k;
	int			m;
	pid_t		pid;
	int			*fd;
	char		*path;
	char		**path_env;
}t_pipeline;

#endif