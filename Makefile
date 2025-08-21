# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/11 20:09:29 by adpinhei          #+#    #+#              #
#    Updated: 2025/08/21 13:15:48 by adpinhei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long

BONUS_NAME := so_long_bonus

CC := cc

FLAGS := -Wall -Wextra -Werror -g -Iincludes -Imlx_linux

vpath %.c src error

LIBFT_PATH := ./libft
LIBFT := $(LIBFT_PATH)/libft.a

MLX_PATH := ./minilibx-linux
MLX_LIB := $(MLX_PATH)/libmlx_Linux.a
MLX_FLAGS := -L$(MLX_PATH) -lmlx -lXext -lX11

BUILD_DIR := build

#Source Files
SRC_FILES := main.c ft_floodfill.c ft_cleanmap.c mapcheck.c \
			libft/get_next_line.c game.c

#SRC_FILES := main_graph.c
#Object Files
OBJ_FILES := $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

#Bonus Sources
BONUS_SRCS := 
#Bonus Objects
BONUS_OBJ := $(BONUS_SRCS:%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean fclean re valgrind norm gdb

all: $(BUILD_DIR) $(LIBFT) $(MLX_LIB) $(NAME)

bonus: $(BUILD_DIR) $(LIBFT) $(BONUS_NAME)

#Compile library LIBFT
$(LIBFT):
	@make --no-print-directory -C $(LIBFT_PATH)

#Compile library libmlx_Linux.a
$(MLX_LIB):
	@make --no-print-directory -C $(MLX_PATH)

#Create BUILD directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $@
	@echo "$(GREEN)Creating$(RESET) $(BUILD_DIR)"
	@echo "$(GREEN)Compiled objects$(RESET)"

#Compile object files into build
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

#Building executable
$(NAME): $(OBJ_FILES) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJ_FILES) $(LIBFT) $(MLX_FLAGS) -o $@
	@echo "$(YELLOW)Compiled$(RESET) $(NAME)"

#Building bonus executable
$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(BONUS_OBJ) $(LIBFT) $(MLX_FLAGS) -o $@
	@echo "$(YELLOW)Compiled bonus executable$(RESET) $(BONUS_NAME)"

norm:
	@norminette -R CheckForbiddenSourceHeader

valgrind: $(NAME)
	@echo "$(YELLOW)Valgrind Report$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes \
	./$(NAME) map_deveriadar.ber

gdb: $(NAME)
	@gdb --tui --args ./$(NAME) map.ber

#Cleanup
clean:
	@rm -rf $(BUILD_DIR)
	@make --no-print-directory -C $(LIBFT_PATH) clean
	@echo "$(BLUE)Cleaned object files$(RESET)"

fclean: clean
	@rm -f $(NAME)
#	@rm -f $(BONUS_NAME)
	@echo "$(BLUE)Erased norminette logfile$(RESET) norma"
	@make --no-print-directory -C $(LIBFT_PATH) fclean
	@echo "$(BLUE)Cleaned executables$(RESET) $(NAME)"

re: fclean all

#Help
help:
	@echo "$(YELLOW)Available targets:$(RESET)"
	@echo "  all           - Build the mandatory executable"
	@echo "  bonus         - Build the bonus executable"
	@echo "  clean         - Remove object files"
	@echo "  fclean        - Remove all built files"
	@echo "  re            - Clean and rebuild everything"
	@echo "  norm          - Run norminette checks"
	@echo "  valgrind      - Run valgrind on mandatory"
#	@echo "  bonusvalgrind - Run valgrind on bonus"
	@echo "  gdb           - Start gdb on mandatory"
#	@echo "  bonusgdb      - Start gdb on bonus"

#Color editing
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

BLUE = \033[1;34m

RESET = \033[0m