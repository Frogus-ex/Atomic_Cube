# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/06 11:20:20 by aautret           #+#    #+#              #
#    Updated: 2026/01/28 12:53:38 by tlorette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D

CC			:= cc

# ————————————— REPERTOIRES —————————————
SRC_		:= src
OBJ_DIR		:= obj
LIBFT_DIR	:= libft
MLX_DIR		:= minilibx-linux
GNL_DIR		:= GNL

# ————————————— MANDATORY —————————————
INCLUDES_DIR_MAND = cub3d_mandatory/includes
SRC_DIR_MAND = cub3d_mandatory/src

CFLAGS		:= -Wall -Wextra -Werror -g -I. -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(INCLUDES_DIR_MAND)

# ————————————— SOURCES OPÉRATIONNELLES —————————————
SRCS := \
	main.c \
	$(SRC_DIR_MAND)/graphic/draw_cub3d.c \
	$(SRC_DIR_MAND)/graphic/draw_map_util.c \
	$(SRC_DIR_MAND)/graphic/draw_minimap.c \
	$(SRC_DIR_MAND)/graphic/graphic_utils.c \
	$(SRC_DIR_MAND)/graphic/init_vision.c \
	$(SRC_DIR_MAND)/graphic/key_handle.c \
	$(SRC_DIR_MAND)/graphic/key_handle_utils.c \
	$(SRC_DIR_MAND)/parsing/floodfill.c \
	$(SRC_DIR_MAND)/parsing/map_copy.c \
	$(SRC_DIR_MAND)/parsing/parsing_identifiers.c \
	$(SRC_DIR_MAND)/parsing/parsing_map.c \
	$(SRC_DIR_MAND)/parsing/parsing_param.c \
	$(SRC_DIR_MAND)/parsing/parsing.c \
	$(SRC_DIR_MAND)/find_id.c \
	$(SRC_DIR_MAND)/init.c \
	$(SRC_DIR_MAND)/cleaner.c \
	$(SRC_DIR_MAND)/utils.c

# ————————————— SOURCES GNL —————————————
GNL_SRCS := \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c

# ————————————— BIBLIOTHÈQUES —————————————
MLX_LIB		:= $(MLX_DIR)/libmlx.a
MLX_REPO	:= https://github.com/42Paris/minilibx-linux.git
MLX_FLAGS	:= -L$(MLX_DIR) -lmlx -lm -lXext -lX11
LIBFT_LIB	:= $(LIBFT_DIR)/libft.a

# ————————————— OBJETS —————————————
OBJS		:= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
GNL_OBJS	:= $(patsubst $(GNL_DIR)/%.c,$(OBJ_DIR)/GNL/%.o,$(GNL_SRCS))
ALL_OBJS	:= $(OBJS) $(GNL_OBJS)

# ————————————— CIBLE PRINCIPALE —————————————
all: $(NAME)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(ALL_OBJS)
	$(CC) $(CFLAGS) $(ALL_OBJS) $(LIBFT_LIB) $(MLX_FLAGS) -o $@
	@echo "$(NAME) created"

# Compile chaque .c en .o (dans OBJ_DIR)
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ---- Compilation des objets GNL ----
$(OBJ_DIR)/GNL/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ---- Sous‑make bibliothèques -------------------------------
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	if [ ! -d $(MLX_DIR) ]; then \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	$(MAKE) -C $(MLX_DIR)

# ---- Cibles de nettoyage -----------------------------------
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d $(MLX_DIR) ]; then $(MAKE) clean -C $(MLX_DIR); fi
	rm -rf $(OBJ_DIR)
	@echo "All object files deleted"

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	@if [ -d $(MLX_DIR) ]; then rm -rf $(MLX_DIR); fi
	rm -f $(NAME)
	@echo "All object files, binary & minilibx deleted"

re: fclean all

.PHONY: all clean fclean re