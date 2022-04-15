# **************************************************************************** #
#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 08:20:09 by cberganz          #+#    #+#              #
#    Updated: 2022/02/27 02:26:37 by cberganz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= philo

INCLUDE		= include/

HEADER		= $(INCLUDE)philosopher.h

CC			= clang

CFLAGS		= -Wall -Wextra -Werror# -g -fsanitize=thread

SRC_FILES 	=	philosopher.c				\
				utils/utils_gen.c			\
				utils/free_data.c			\
				utils/utils_print.c			\
				parsing/argument_error.c	\
				parsing/initialize_data.c	\
				parsing/initialize_mutex.c	\
				exec/initialize_thread.c	\
				exec/philo_exec.c

SRC_DIR		= src/
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		= objs/
OBJ_DIRS	= $(sort $(dir $(OBJ)))
OBJ_FILES	= $(SRC_FILES:.c=.o)
OBJ			= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(NAME)

$(NAME): ECHO_COMPIL $(OBJ)
	@echo -n Compiling executable $(NAME)...
	@$(CC) $(CFLAGS) $(OBJ) -lpthread -o $(NAME)
	@echo "\033[92m Done.\033[0m"

ECHO_COMPIL:
	@echo Compiling philosopher files...

$(OBJ_DIRS):
	@mkdir -p $@

$(OBJ): | $(OBJ_DIRS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	@echo -n Making clean...
	@rm -rf $(OBJ_DIR)
	@echo "\033[92m Done.\033[0m"

fclean: clean
	@echo -n Making fclean...
	@rm -f $(NAME)
	@echo "\033[92m Done.\033[0m"

re: fclean all

.PHONY : all clean fclean re
