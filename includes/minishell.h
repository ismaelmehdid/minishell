/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:28 by imehdid           #+#    #+#             */
/*   Updated: 2024/03/23 23:19:33 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "pipeline.h"
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
# include <sys/wait.h>

typedef enum s_redirection
{
	IN,
	OUT,
	APPEND,
	HERE_DOC
}	t_redirection;

typedef enum s_nodetype
{
	COMMAND_NODE,
	PIPE_NODE,
	UNRECOGNIZED_NODE
}	t_nodetype;

typedef struct s_astnode
{
	t_nodetype			type;
	char				*value;
	struct s_astnode	*left;
	struct s_astnode	*right;
	int					*quotes_indexes;
	int					starting_index;
}	t_astnode;

typedef struct s_list
{
	char							*content;
	struct s_list					*next;
}	t_list;

//-------Env utils-------======================================================
void			free_list(t_list **env);
char			**create_envp(t_list *env);
int				ft_lstsize(t_list *lst);
int				create_env(t_list **env, char **envp);
//-------Parsing-----------=======================
t_astnode		*parsing(char **input);
t_astnode		*init_ast(char **elements);
t_astnode		*create_node(char *element);
enum s_nodetype	get_element_type(char *element);
char			*pipes_validation(char *input);
int				check_last_pipe_command(char *inp);
int				check_for_spaces(char *inp);
char			*get_backup(char *backup, char *input);
int				quotes_validation(char **elements);
//-------Parsing utils----========================
void			free_double_array(char **array);
void			free_all_nodes(t_astnode *root);
int				ft_strcmp(char *one, char *two);
int				contain_str(char **array, char *element);
void			skip_quotes(char *input, int *i);
//-------Split elements---========================
char			**split_quotes(char *input, char *skip);
void			skip_quotes(char *input, int *i);
int				count_words(char *input, char *skip);
char			*malloc_word(char *input, int *i, char *skip);
void			copy_word(char *result, char *input, int *i, char *skip);
int				size_double_array(char **array);
//-------Signals-------========================
int				toggle_echoctl_status(int status);
void			ctrl_c(int signum);
void			new_ctrl_c(int signum);
void			new_ctrl_c_pipe(int signum);
int				check_num(int num1, int num2);
//-------Execution-------========================
void			init_executor(t_astnode *root, t_list **env);
int				execute_pipeline(char **cmds, t_list **env, t_astnode *root);
int				launch_executable(char *cmd, char **envp);
//-------Execution utils-------==================
char			*get_path(char *cmd, char *path_full);
void			close_pipe_fds(int *fd, int size);
t_pipeline		get_pipe_utils(char **cmds);
void			launch_cmd(char *cmd, char **envp, char *cmd_path);
void			not_found(char *cmd);
//-------Built-ins-------========================
int				handle_builtin(char *input, char **envp, t_list **env, t_astnode *root);
int				execute_echo(char *arg, t_astnode *root, t_list **env);
int				execute_pwd(void);
int				execute_export(char *arg, t_list *env, char **envp);
int				execute_env(char **envp);
void			execute_exit(char *input, t_list **env, t_astnode *root, char **envp);
int				execute_cd(char *path, t_list **env);
int				prepare_cd(char *path, char *thepath);
int				execute_unset(t_list **head, char *key);
int				update_old_pwd_dir(t_list **env, char *cwd);
int				update_pwd(t_list **env);
int				get_home_dir(char **home, t_list **env);
int				get_old_pwd(t_list **env, char **old_pwd);
t_list			*get_last_node(t_list *lst);
int				export_print_error(char *arg);
int				search_replace_existing_cmp(t_list *lst, char *arg);
//-------Redirection----=======================
int				dup_error(int fds[2]);
void			restore_std(int fds[2]);
int				get_flags(t_redirection type);
int				init_redirection(char **redirections, int fds[2], int status, int i);
void			del_redirs_from_root(t_astnode **root);
char			**create_redirs(t_astnode *root);
t_redirection	get_redir_type(char *redirection);
char			*get_redirection(char *line);
int				redir_exist(char *line);
int				count_redirs(t_astnode *node);
int				still_exist(char *line);
int				here_doc(char *delimeter, int fd, int dup_return, int in_flag);
char			*ft_strjoin_free(char *s1, char const *s2, int s2_len);
int				write_to_tmp_file(int fd, char *input);
void			unlink_file(char *msg);
int				write_from_stdin_to_fd(int *fd, int	bytes_read, int bytes_written);
//---------------------========================
char			*check_and_modify(char *input, int append, int out);
int				count_out(char *input);
int				is_whitespace(char c);
int				count_append(char *input);
int				get_next_index(char *line, int last);
int				get_last_index(char *input);
int				get_prelast_file(char *input, int i);

void			print_prompt(int status);

extern int						g_last_command_status;
extern int						g_stdin_copy_fd;
extern volatile sig_atomic_t	g_sig_pressed;

#endif