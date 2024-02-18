/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:28 by imehdid           #+#    #+#             */
/*   Updated: 2024/02/18 15:48:44 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define CLEAR_SCREEN "\033[2J\033[H"

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <curses.h>
#include <termcap.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>

void	program_exit(int code);
int		handle_commands(char *input);
void	handle_signals(void);

//---------------------========================
int		handle_builtin(char *input);
void	execute_pwd(void);
void	execute_export(void);
void	execute_env(void);
void	execute_unset(void);
//---------------------========================

#endif