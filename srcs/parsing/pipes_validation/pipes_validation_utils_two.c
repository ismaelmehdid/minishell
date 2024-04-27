/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_validation_utils_two.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:08:15 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/27 16:57:58 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	leaks_signal_fix(char *backup, int orig_stdin)
{
	close(orig_stdin);
	signal(SIGQUIT, ctrl_back_slash);
	if (backup)
		free(backup);
}
