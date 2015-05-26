# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/11 01:49:54 by amaurer           #+#    #+#              #
#    Updated: 2015/05/08 04:28:42 by amaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=	src/
OBJ_DIR		=	build/
INC_DIR		=	include libs/libft/includes
BIN_DIR		=	bin/

NAME		=	wav
BIN_NAME	=	$(BIN_DIR)$(NAME)
SRC_FILES	=	main.c \
				generator/generator.c \
				player.c \
				util.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))

CC			=	clang
CC_FLAGS	=	-Wall -Werror -Wextra
CC_LIBS		=	-lft -Llibs/libft -framework AudioToolbox -framework CoreFoundation -lm

all: libft $(BIN_NAME)
	@echo "\033[32m•\033[0m $(NAME) is ready."

$(BIN_NAME): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_NAME) $(CC_LIBS) $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(subst $() $(), -I, $(INC_DIR)) -o $@ -c $<

clean:
	make -C libs/libft clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C libs/libft fclean
	rm -rf $(BIN_NAME)

re: fclean all

libft:
	@make -C libs/libft

.PHONY: all re fclean clean libs