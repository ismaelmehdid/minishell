/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:34:28 by imehdid           #+#    #+#             */
/*   Updated: 2024/04/27 17:52:12 by imehdid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//=== Includes ------------------------------------------------------------===//

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/wait.h>

//=== Data structures -----------------------------------------------------===//

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
}	t_astnode;

typedef struct s_list
{
	char							*content;
	bool							export_marked;
	bool							export_marked_sub;
	bool							value_assigned;
	struct s_list					*next;
}	t_list;

typedef struct s_pipeline
{
	int			i;
	int			j;
	int			k;
	int			m;
	pid_t		pid;
	int			*fd;
	int			fds[2];
	char		**redirs;
	char		**cmds;
}	t_pipeline;

typedef struct s_cpy_word_indexes
{
	int	i;
	int	k;
}	t_cpy_word_indexes;

//=== Utils ---------------------------------------------------------------===//

void			free_list(t_list **env);
char			**create_envp(t_list *env);
int				ft_lstsize(t_list *lst, bool count_only_env);
int				create_env(t_list **env, char **envp);
int				restore_stdin(int check_num, int orig_stdin);

//=== Parsing -------------------------------------------------------------===//

t_astnode		*parsing(char **input, t_list *env);
t_astnode		*init_ast(char **elements);
t_astnode		*create_node(char *element);
char			*pipes_validation(
					char *input,
					t_list **env,
					char *backup,
					int orig_stdin);
void			exit_program(char *backup, t_list **env);
int				check_last_pipe_command(char *inp);
int				check_for_spaces(char *inp);
char			*get_backup(char *backup, char *input);
int				quotes_validation(char *elements);
int				is_whitespace(char c);

//=== Parsing utils -------------------------------------------------------===//

void			free_double_array(char **array);
int				redir_syntax_checker(char *input);
void			free_all_nodes(t_astnode *root);
int				ft_strcmp(char *one, char *two);
int				contain_str(char **array, char *element);
void			skip_quotes(char *input, int *i);
int				only_spaces(char *line);
char			*print_parse_error(char *input, int i);
void			leaks_signal_fix(char *backup, int orig_stdin);

//=== Split elements ------------------------------------------------------===//

char			**split_quotes_bash(char *input, char *skip, t_list *env);
void			skip_quotes(char *input, int *i);
int				count_words(char *input, char *skip, int i);
char			*malloc_word(char *input, int *i, char *skip, t_list *env);
int				copy_word(char *result, char *input, char *skip, t_list *env);
int				size_double_array(char **array);
int				search_env_size(char *input, int *i, t_list *env);
void			add_env_value(
					char *result,
					char *input,
					t_cpy_word_indexes *indexes,
					t_list *env);
int				get_variable_name(char *input, int i, char *dest);
int				env_var_name_size(char *env_var);

//=== Signals -------------------------------------------------------------===//

void			ctrl_c(int signum);
void			new_ctrl_c(int signum);
void			ctrl_back_slash(int signum);

//=== Execution -----------------------------------------------------------===//

void			init_executor(t_astnode *root, t_list **env);
int				execute_pipeline(
					t_pipeline *utl,
					t_list **env,
					t_astnode *root);
void			launch_executable(char *cmd, char **envp, int i);

//=== Execution utils -----------------------------------------------------===//

char			*get_path(char *cmd, char *path_full);
void			close_pipe_fds(int *fd, int size);
void			get_pipe_utils(t_pipeline **utl);
int				get_pipe_size(t_astnode *node);
int				init_pipe(t_astnode *node, t_list **env, int counter);
void			launch_cmd(char *cmd, char **envp, char *cmd_path, char **cmds);
void			print_error_not_found(char *cmd, int code);
int				get_command(char *input, char *checking);
int				get_cmd_args_index(char *input);
t_list			*free_copy_list(char *content, t_list *listptr);
int				mystrcmp(const char *first, const char *second);
char			*get_content(t_astnode *node);
int				check_empty_status(char *cmds);
void			stop_exec(t_pipeline *utl);
void			free_pipeline_util(t_pipeline *utl);
int				handle_fds_dup(char **cmds, t_pipeline *utl);

//=== Built-ins -----------------------------------------------------------===//

int				handle_builtin(
					char *input,
					t_list **env,
					t_astnode *root,
					int fds[2]);
int				execute_echo(char *arg);
int				execute_pwd(void);
int				execute_export(char *arg, t_list **env);
bool			value_exist(t_list *lst, char *arg);
int				show_exported_var_list(t_list *env, char **exports);
int				checking_errors(char **exports);
int				execute_env(char **envp, char *args);
void			execute_exit(
					char *input,
					t_list **env,
					t_astnode *root,
					char **envp);
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
int				trim_quotes(char **args);

//=== Redirections --------------------------------------------------------===//

int				make_redirection(char **redirs, int fds[2], int i);
int				dup_error(int fds[2]);
void			restore_std(int fds[2]);
int				get_flags(t_redirection type);
t_redirection	redir_type(char *redirection);
int				pre_here_doc(char *redir, int fds[2]);
char			*get_file_redir(char *rediction);
int				here_doc(char *delimiter,
					int fd,
					int dup_return,
					int orig_stdin);
char			*ft_strjoin_free(char *s1, char const *s2, int s2_len);
int				write_to_tmp_file(int fd, char *input);
void			unlink_file(char *msg);
void			no_such_file_error(char *file);
int				here_doc_exist(char **redirs, int i);
void			useless_here_doc(char **redirs, int i, int orig_stdin);
int				no_cmds(t_astnode *root);
int				stop_exec_cmd(int fds[2]);
int				backup_std(int fds[2]);

//=== Redirection List of Char Creation -----------------------------------===//

char			**create_list(t_astnode *root);
void			del_redirs_from_root(t_astnode **root);
int				redir_exist(char *line);
int				get_index_after_quotes(char *line);
int				count_redirs(t_astnode *node);
int				still_exist(char *line);

//=== Global variables ----------------------------------------------------===//

extern int						g_last_command_status;

#endif
