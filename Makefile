# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 16:16:03 by fmonbeig          #+#    #+#              #
#    Updated: 2021/12/13 17:55:40 by fmonbeig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME := $(shell uname)


ifeq ($(UNAME), Linux)
ADDONS		= -L/usr/include -pthread
endif
ifeq ($(UNAME), Darwin)
ADDONS		=
endif

NAME			= philo
CC				= clang
FLAGS			= -Wall -Werror -Wextra
HEADERS			= include/
SRC_PATH		= src/

SRC			= \
			$(SRC_PATH)main.c \
			$(SRC_PATH)thread_vital.c \
			$(SRC_PATH)thread_philo.c \
			$(SRC_PATH)init.c \
			$(SRC_PATH)close.c \
			$(SRC_PATH)state.c \
			$(SRC_PATH)utils.c \
			$(SRC_PATH)fork.c \
			$(SRC_PATH)utils_libft.c \
			$(SRC_PATH)error.c \
			$(SRC_PATH)message.c \

OBJS		= $(SRC:.c=.o)

$(NAME):	$(OBJS)
			@echo "\\n\033[34;1m ***PHILOSOPHERS COMPILATION*** \033[0m \\n"
			@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(ADDONS)
			@echo "\\n\033[31;1m --- COMPILATION FINISH --- \033[0m \\n"

all: 		$(NAME)

clean:
			@rm -rf $(OBJS)

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
