/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:28 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/19 01:14:14 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CLEAR_SCREEN "\033[2J\033[H"

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

typedef enum s_nodetype
{
	COMMAND_NODE,
	FLAG_NODE,
	ARGUMENT_NODE,
	REDIRECTION_NODE,
	PIPE_NODE,
	UNRECOGNIZED_NODE
}	t_nodetype;

typedef struct s_astnode
{
	t_nodetype			type;
	char				*value;
	struct s_astnode	*left;
	struct s_astnode	*right;
}	t_astnode;

//---------------------========================
void	program_exit(int code);
int		handle_commands(char *input);
void	handle_signals(void);
//---------------------========================
int		handle_builtin(char *input);
int		execute_pwd(void);
int		execute_export(void);
int		execute_env(void);
int		execute_unset(void);
//---------------------========================



//-------Parsing-------========================
t_astnode	*parsing(char *input);
t_astnode	*init_ast(char **elements);
t_astnode *create_node(char *element);
enum s_nodetype	get_element_type(char *element);
//---------------------========================



//----Parsing utils----========================
void	free_double_array(char **array);
void	free_all_nodes(t_astnode *root);
int		ft_strcmp(char *one, char *two);
int		contain_str(char **array, char *element);
//---------------------========================

#endif