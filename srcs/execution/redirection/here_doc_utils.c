/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 23:18:03 by asyvash           #+#    #+#             */
/*   Updated: 2024/04/03 12:25:47 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int if_there_was_out_append(char **redirs, int i)
{
	int j;
	int check_val;
	
	j = 0;
	check_val = 1;
	while(j < i)
	{
		if (ft_strncmp(redirs[j], ">", 1) == 0 || \
			ft_strncmp(redirs[j], ">>", 2) == 0)
			check_val = 0;
		j++;
	}
	return (check_val);	
}

int if_there_was_in(char **redirs, int i)
{
	int j;
	int check_val;
	
	j = 0;
	check_val = 1;
	while(j < i)
	{
		if (ft_strncmp(redirs[j], "<", 1) == 0)
			check_val = 0;
		j++;
	}
	return (check_val);	
}

int	get_quantity(char **redirs)
{
	int i;
	int	quantity;

	i = 0;
	quantity = 0;
	while (redirs[i])
	{
        if (ft_strncmp(redirs[i], "<<", 2) == 0)
            quantity++;
		i++;
	}
	return (quantity);
}