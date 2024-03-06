/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:31:31 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/04 22:39:22 by asyvash          ###   ########.fr       */
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
}t_pipeline;

#endif