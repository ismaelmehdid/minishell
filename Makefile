NAME = minishell

SRCS = $(wildcard srcs/*.c srcs/parsing/*.c srcs/execution/*.c \
		srcs/errors_handling/*.c srcs/execution/builtin/*.c \
		srcs/parsing/spliting_elements/*.c srcs/parsing/pipes_validation/*.c \
		srcs/parsing/quotes_validation/*.c \
		srcs/execution/redirection/*.c srcs/execution/pipes/*.c)

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