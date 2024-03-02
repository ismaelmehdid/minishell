# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 19:34:20 by imehdid           #+#    #+#              #
#    Updated: 2024/03/02 21:35:18 by imehdid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = ${wildcard srcs/*.c srcs/parsing/*.c srcs/execution/*.c srcs/errors_handling/*.c srcs/execution/builtin/*.c srcs/parsing/spliting_elements/*.c srcs/parsing/syntax_checker/*.c srcs/parsing/pipes_validation/*.c srcs/parsing/quotes_validation/*.c}

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -Iincludes

RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
		@${MAKE} -C ./includes/libft
		 @${CC} ${CFLAGS} ${OBJS} ./includes/libft/libft.a -o ${NAME} -lreadline

clean:
		@${MAKE} -C ./includes/libft fclean
		@${RM} ${OBJS}

fclean: clean
		@${RM} ${NAME} ${OBJS}

re: fclean all

.PHONY: all clean fclean re