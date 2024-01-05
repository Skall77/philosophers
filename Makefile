# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaudevar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 09:52:50 by aaudevar          #+#    #+#              #
#    Updated: 2023/02/03 15:15:53 by aaudevar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = 	philo.c \
		utils.c \
		time.c \
		init.c \
		threads.c \
		mutex.c \
		routine.c \

OBJS = ${SRCS:.c=.o}

NAME = philo
LFT = libft.a
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -pthread
HEADER = philo.h

%.o: %.c ${HEADER}
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${INCLUDE} -o ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re