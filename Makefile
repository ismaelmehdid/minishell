# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imehdid <ismaelmehdid@student.42.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 19:34:20 by imehdid           #+#    #+#              #
#    Updated: 2024/02/15 19:54:25 by imehdid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = ${wildcard *.c}

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
		 @${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
		@${RM} ${OBJS}

fclean: clean
		@${RM} ${NAME} ${OBJS} ${NAME_BONUS}

re: fclean all

.PHONY: all clean fclean re