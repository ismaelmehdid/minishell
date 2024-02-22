/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:13:05 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/22 15:22:10 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	syntax_checker_env(t_astnode *root)
{
	if (root->left || root->right)
	{
		printf("Minishell: option(s) or argument(s) incorrect: %s\n",
			root->value);
		return (1);
	}
	return (0);
}

int	syntax_checker(t_astnode *root)
{
	if (root->type != COMMAND_NODE)
	{
		printf("Minishell: command not found: %s\n", root->value);
		return (1);
	}
	if (syntax_checker_env(root))
		return (1);
	return (0);
}
