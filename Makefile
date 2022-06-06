# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 17:05:57 by sichoi            #+#    #+#              #
#    Updated: 2022/06/06 19:53:04 by swi              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

MLX_NAME = libmlx.dylib
MLX_DIR = ./mlx
LIB_MLX = $(MLX_DIR)/$(MLX_NAME)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -03
#CFLAGS = -O3

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
CHECK = \033[0;32m\xE2\x9C\x94\033[0m

FUNC = main\
	   base/ft_memset\
	   base/print_error\
	   base/ft_strlen\
	   base/ft_strcmp\
	   base/ft_read\
	   base/malloc_array\
	   base/ft_realloc\
	   base/stox

SRC = $(addsuffix .c, $(FUNC))
OBJ = $(addsuffix .o, $(FUNC))

%.o : %.c
	@echo "$(NAME): $(GREEN) compiling... $< $(CHECK) $(RESET)"
	@$(CC) -I $(MLX_DIR) -o $@ -c $<

$(NAME) : $(LIB_MLX) $(OBJ)
	@$(CC) -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJ)
	@echo "$(NAME): $(GREEN) $(NAME) was created! $(CHECK) $(RESET)"
	@install_name_tool -change libmlx.dylib $(LIB_MLX) $(NAME)
	@echo "$(NAME): $(GREEN) Completed Setting Path of $(MLX_NAME) $(CHECK) $(RESET)"

$(LIB_MLX):
	$(MAKE) -sC $(MLX_DIR)
	@echo "$(NAME): $(GREEN) $(MLX_NAME) was created! $(CHECK) $(RESET)"

all : $(NAME)

clean :
	@$(MAKE) -sC $(MLX_DIR) clean
	@rm -f $(OBJ)
	@echo "$(NAME): $(RED) object files deleted $(RESET)"

fclean : clean
	@rm -f $(LIB_MLX)
	@echo "$(NAME): $(RED) $(MLX_NAME) was deleted $(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED) $(NAME) was deleted $(RESET)"

re : fclean all
