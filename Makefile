# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aautret <aautret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/06 11:20:20 by aautret           #+#    #+#              #
#    Updated: 2026/01/29 14:22:44 by aautret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D
NAME_BONUS	:= cub3D_bonus
CC			:= cc

# ————————————— REPERTOIRES —————————————
OBJ_DIR		:= obj
OBJ_DIR_BONUS := obj_bonus
LIBFT_DIR	:= libft
MLX_DIR		:= minilibx-linux
GNL_DIR		:= GNL

# ————————————— MANDATORY —————————————
INCLUDES_DIR_MAND := cub3d_mandatory/includes
SRC_DIR_MAND := cub3d_mandatory/src

# —————————————— BONUS —————————————————
INCLUDES_DIR_BONUS := cub3d_bonus/includes_bonus
SRC_DIR_BONUS := cub3d_bonus/src_bonus

# ————————————— FLAGS —————————————
CFLAGS		:= -Wall -Wextra -Werror -g -I. -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR)
CFLAGS_MAND	:= $(CFLAGS) -I$(INCLUDES_DIR_MAND)
CFLAGS_BONUS := $(CFLAGS) -I$(INCLUDES_DIR_BONUS)

# ————————————— SOURCES MANDATORY —————————————
SRCS_MAND := \
    $(SRC_DIR_MAND)/main.c \
    $(SRC_DIR_MAND)/clean/cleaner.c \
    $(SRC_DIR_MAND)/game/draw_game.c \
    $(SRC_DIR_MAND)/game/game_utils.c \
    $(SRC_DIR_MAND)/game/manage_moves.c \
    $(SRC_DIR_MAND)/game/manage_moves_utils.c \
    $(SRC_DIR_MAND)/game/manage_textures.c \
    $(SRC_DIR_MAND)/game/raycaster.c \
    $(SRC_DIR_MAND)/game/raycast_utils.c \
    $(SRC_DIR_MAND)/initialisation/init_textures.c \
    $(SRC_DIR_MAND)/initialisation/init.c \
    $(SRC_DIR_MAND)/parsing/floodfill.c \
    $(SRC_DIR_MAND)/parsing/map_copy.c \
    $(SRC_DIR_MAND)/parsing/parsing_identifiers.c \
    $(SRC_DIR_MAND)/parsing/parsing_map.c \
    $(SRC_DIR_MAND)/parsing/parsing_param.c \
    $(SRC_DIR_MAND)/parsing/parse_rgb_text.c \
    $(SRC_DIR_MAND)/parsing/parsing.c \
    $(SRC_DIR_MAND)/utils/utils.c

# ————————————— SOURCES BONUS —————————————
SRCS_BONUS := \
    $(SRC_DIR_BONUS)/main.c \
    $(SRC_DIR_BONUS)/clean_bonus/cleaner.c \
    $(SRC_DIR_BONUS)/game_bonus/draw_game.c \
    $(SRC_DIR_BONUS)/game_bonus/game_utils.c \
    $(SRC_DIR_BONUS)/game_bonus/manage_moves.c \
    $(SRC_DIR_BONUS)/game_bonus/manage_moves_utils.c \
    $(SRC_DIR_BONUS)/game_bonus/manage_textures.c \
    $(SRC_DIR_BONUS)/game_bonus/raycaster.c \
    $(SRC_DIR_BONUS)/game_bonus/raycast_utils.c \
    $(SRC_DIR_BONUS)/initialisation_bonus/init_textures.c \
    $(SRC_DIR_BONUS)/initialisation_bonus/init.c \
    $(SRC_DIR_BONUS)/parsing_bonus/floodfill.c \
    $(SRC_DIR_BONUS)/parsing_bonus/map_copy.c \
    $(SRC_DIR_BONUS)/parsing_bonus/parsing_identifiers.c \
    $(SRC_DIR_BONUS)/parsing_bonus/parsing_map.c \
    $(SRC_DIR_BONUS)/parsing_bonus/parsing_param.c \
    $(SRC_DIR_BONUS)/parsing_bonus/parse_rgb_text.c \
    $(SRC_DIR_BONUS)/parsing_bonus/parsing.c \
    $(SRC_DIR_BONUS)/utils_bonus/utils.c

# ————————————— SOURCES GNL —————————————
GNL_SRCS := \
    $(GNL_DIR)/get_next_line.c \
    $(GNL_DIR)/get_next_line_utils.c

# ————————————— BIBLIOTHÈQUES —————————————
MLX_LIB		:= $(MLX_DIR)/libmlx.a
MLX_REPO	:= https://github.com/42Paris/minilibx-linux.git
MLX_FLAGS	:= -L$(MLX_DIR) -lmlx -lm -lXext -lX11
LIBFT_LIB	:= $(LIBFT_DIR)/libft.a

# ————————————— OBJETS MANDATORY —————————————
OBJS_MAND	:= $(patsubst $(SRC_DIR_MAND)/%.c,$(OBJ_DIR)/%.o,$(SRCS_MAND))
GNL_OBJS_MAND := $(patsubst $(GNL_DIR)/%.c,$(OBJ_DIR)/GNL/%.o,$(GNL_SRCS))
ALL_OBJS_MAND := $(OBJS_MAND) $(GNL_OBJS_MAND)

# ————————————— OBJETS BONUS —————————————
OBJS_BONUS	:= $(patsubst $(SRC_DIR_BONUS)/%.c,$(OBJ_DIR_BONUS)/%.o,$(SRCS_BONUS))
GNL_OBJS_BONUS := $(patsubst $(GNL_DIR)/%.c,$(OBJ_DIR_BONUS)/GNL/%.o,$(GNL_SRCS))
ALL_OBJS_BONUS := $(OBJS_BONUS) $(GNL_OBJS_BONUS)

# ————————————— CIBLE PRINCIPALE —————————————
all: $(NAME)

# ————————————— COMPILATION MANDATORY —————————————
$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(ALL_OBJS_MAND)
	$(CC) $(CFLAGS_MAND) $(ALL_OBJS_MAND) $(LIBFT_LIB) $(MLX_FLAGS) -o $@
	@echo "✅ $(NAME) (mandatory) created"

# Compile chaque .c en .o pour mandatory
$(OBJ_DIR)/%.o: $(SRC_DIR_MAND)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_MAND) -c $< -o $@

# Compile GNL pour mandatory
$(OBJ_DIR)/GNL/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_MAND) -c $< -o $@

# ————————————— COMPILATION BONUS —————————————
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT_LIB) $(MLX_LIB) $(ALL_OBJS_BONUS)
	$(CC) $(CFLAGS_BONUS) $(ALL_OBJS_BONUS) $(LIBFT_LIB) $(MLX_FLAGS) -o $@
	@echo "✅ $(NAME_BONUS) created"

# Compile chaque .c en .o pour bonus
$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_BONUS) -c $< -o $@

# Compile GNL pour bonus
$(OBJ_DIR_BONUS)/GNL/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_BONUS) -c $< -o $@

# ————————————— BIBLIOTHÈQUES —————————————
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "📥 Cloning minilibx..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	$(MAKE) -C $(MLX_DIR)

# ————————————— NETTOYAGE —————————————
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d $(MLX_DIR) ]; then $(MAKE) clean -C $(MLX_DIR); fi
	rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@echo "🧹 All object files deleted"

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	@if [ -d $(MLX_DIR) ]; then rm -rf $(MLX_DIR); fi
	rm -f $(NAME) $(NAME_BONUS)
	@echo "🗑️  All binaries & minilibx deleted"

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonusj