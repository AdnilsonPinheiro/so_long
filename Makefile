# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/11 20:09:29 by adpinhei          #+#    #+#              #
#    Updated: 2025/09/03 20:12:03 by adpinhei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long

BONUS_NAME := so_long_bonus

CC := cc

FLAGS := -Wall -Wextra -Werror -g -Iincludes -Imlx_linux

vpath %.c src error src_bonus

LIBFT_PATH := ./libft
LIBFT := $(LIBFT_PATH)/libft.a

MLX_PATH := ./minilibx-linux
MLX_LIB := $(MLX_PATH)/libmlx_Linux.a
MLX_FLAGS := -L$(MLX_PATH) -lmlx -lXext -lX11

BUILD_DIR := build

#Source Files
SRC_FILES := main.c ft_floodfill.c clean_fts.c mapcheck.c \
			moves.c image.c utils.c \
			libft/get_next_line.c game.c

#Object Files
OBJ_FILES := $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

#Bonus Sources
BONUS_SRCS := main_bonus.c ft_floodfill_bonus.c clean_fts_bonus.c mapcheck_bonus.c \
			moves_bonus.c image_bonus.c utils_bonus.c \
			libft/get_next_line.c game_bonus.c
#Bonus Objects
BONUS_OBJ := $(BONUS_SRCS:%.c=$(BUILD_DIR)/%.o)

#Norminette Directories
NORM_DIRS := src includes error src_bonus

.PHONY: all clean fclean re valgrind norm gdb

all: $(BUILD_DIR) $(LIBFT) $(MLX_LIB) $(NAME)

bonus: $(BUILD_DIR) $(LIBFT) $(BONUS_NAME)

#Compile library LIBFT
$(LIBFT):
	@make --no-print-directory -C $(LIBFT_PATH)

#Compile library libmlx_Linux.a
# Compile library libmlx_Linux.a
$(MLX_LIB):
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo "$(YELLOW)minilibx not found. Cloning from GitHub...$(RESET)"; \
		git clone https://github.com/42paris/minilibx-linux.git $(MLX_PATH) || { \
			echo "$(RED)Failed to clone repository$(RESET)"; \
			exit 1; \
		}; \
	fi
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
	@for dir in $(NORM_DIRS); do \
		echo "$(GREEN)Checking $$dir...$(RESET)"; \
		norminette -R CheckForbiddenSourceHeader $$dir; \
	done

valgrind: $(NAME)
	@echo "$(YELLOW)Valgrind Report$(RESET)"
	@valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--track-fds=yes \
	./$(NAME) ./maps/map.ber

bonusvalgrind: $(BONUS_NAME)
	@echo "$(YELLOW)Valgrind Report$(RESET)"
	@valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--track-fds=yes \
	./$(BONUS_NAME) ./maps_bonus/map.ber

gdb: $(NAME)
	@gdb --tui --args ./$(NAME) ./maps/map.ber

#Cleanup
clean:
	@rm -rf $(BUILD_DIR)
	@make --no-print-directory -C $(LIBFT_PATH) clean
	@echo "$(BLUE)Cleaned object files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -rf test_log
	@echo "$(BLUE)Cleaned test_log$(RESET)"
	@rm -f $(BONUS_NAME)
	@make --no-print-directory -C $(LIBFT_PATH) fclean
	@echo "$(BLUE)Cleaned executables$(RESET) $(NAME) $(BONUS_NAME)"

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
	@echo "  bonusvalgrind - Run valgrind on bonus"
	@echo "  gdb           - Start gdb on mandatory"
#	@echo "  bonusgdb      - Start gdb on bonus"

#Color editing
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

BLUE = \033[1;34m

RESET = \033[0m