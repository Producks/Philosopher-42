# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/12 12:36:12 by ddemers           #+#    #+#              #
#    Updated: 2023/02/12 18:13:17 by ddemers          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable #
NAME = philo_bonus
# Compile stuff #
CC = gcc
#CFGLAGS = -g -Wall -Werror -Wextra -pthread
#CFGLAGS = -Wall -Werror -Wextra -fsanitize=thread -g -pthread
CFGLAGS = -Wall -Werror -Wextra -pthread
# Remove #
REMOVE = rm -f
# Run #
RUN = ./philo
# OBJS #
OBJS = ${SRC:.c=.o}
# Source #
SRC = 	./src/main.c \
		./src/parsing.c \
		./src/utils.c \
		./src/semaphore.c \
		./src/thread.c
# Colors #
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

$(NAME): $(OBJS)
		${CC} ${CFGLAGS} ${OBJS} ${FLAGS} -o ${NAME}

all: ${NAME}

clean:
	${REMOVE} ${OBJS}

fclean:clean
	${REMOVE} ${NAME}

re: fclean all

run: ${NAME} ${RUN}

.PHONY: all clean fclean re