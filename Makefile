NAME = minishell

SRCS =	srcs/env_utils.c \
        srcs/minishell.c \
		srcs/list_utils.c \
        srcs/basic_utils.c \
        srcs/parsing/parsing.c \
        srcs/parsing/redir_syntax_check.c \
        srcs/parsing/parsing_utils.c \
        srcs/parsing/pipes_validation/pipe_validation.c \
        srcs/parsing/pipes_validation/pipes_validation_utils.c \
        srcs/parsing/pipes_validation/pipes_validation_utils_two.c \
        srcs/parsing/quotes_validation/quotes_validation.c \
        srcs/parsing/spliting_elements/get_env_size.c \
        srcs/parsing/spliting_elements/get_env_value.c \
        srcs/parsing/spliting_elements/split_elements.c \
        srcs/parsing/spliting_elements/split_elements_copy.c \
        srcs/parsing/spliting_elements/split_elements_malloc.c \
        srcs/execution/handle_signals.c \
        srcs/execution/init_execution.c \
        srcs/execution/launch_executable.c \
        srcs/execution/get_path.c \
        srcs/execution/builtin/cd.c \
        srcs/execution/builtin/cd_utils.c \
        srcs/execution/builtin/cd_utils_two.c \
        srcs/execution/builtin/echo.c \
        srcs/execution/builtin/env.c \
        srcs/execution/builtin/export.c \
        srcs/execution/builtin/export_print.c \
        srcs/execution/builtin/export_utils.c \
        srcs/execution/builtin/export_utils_two.c \
        srcs/execution/builtin/export_utils_three.c \
        srcs/execution/builtin/handle_builtin.c \
        srcs/execution/builtin/handle_builtin_utils.c \
        srcs/execution/builtin/pwd.c \
        srcs/execution/builtin/exit.c \
        srcs/execution/builtin/unset.c \
        srcs/execution/pipes/execute_pipes.c \
        srcs/execution/pipes/child_process.c \
        srcs/execution/pipes/pipe_utils.c \
        srcs/execution/pipes/pipe_utils_two.c \
        srcs/execution/pipes/pipe_utils_three.c \
        srcs/execution/pipes/pre_exec_pipes.c \
        srcs/execution/pipes/execute_exit_in_pipe.c \
        srcs/execution/redirection/here_doc.c \
        srcs/execution/redirection/here_doc_utils.c \
        srcs/execution/redirection/specific_utils.c \
        srcs/execution/redirection/list_creation.c \
        srcs/execution/redirection/list_creation_utils.c \
        srcs/execution/redirection/redirs.c \
        srcs/execution/redirection/redirs_utils.c

OBJS_DIR = objs/
OBJS = $(patsubst srcs/%.c,$(OBJS_DIR)%.o,$(SRCS))

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -Iincludes

RM = rm -rf

CLEAR = clear

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C ./includes/libft
	@$(CC) $(CFLAGS) $(OBJS) ./includes/libft/libft.a -o $(NAME) -lreadline
	@$(CLEAR)
	@printf "\033[1;32m$(NAME) built successfully\033[0m\n"

$(OBJS_DIR)%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@printf "\033[1;36mCompiling $<\033[0m\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C ./includes/libft fclean
	@$(RM) $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

