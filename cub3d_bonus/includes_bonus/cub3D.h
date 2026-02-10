/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:13:10 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/10 12:48:25 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define _USE_MATH_DEFINES
# define _GNU_SOURCE

# include "GNL/get_next_line.h"
# include "config.h"
# include "game.h"
# include "libft/libft.h"
# include "minimap.h"
# include "mlx.h"
# include <fcntl.h>
# include <float.h>
# include <libft.h>
# include <math.h>
# include <stdio.h>
# include <time.h>
# include <unistd.h>

typedef enum e_parse_state
{
	PARSES_IDENTIFIERS,
	PARSE_MAP
}				t_parse_state;

typedef struct s_player
{
	int			origin_y;
	int			origin_x;
	int			view_distance;
	int			w_pressed;
	int			s_pressed;
	int			a_pressed;
	int			d_pressed;
	int			left_pressed;
	int			right_pressed;
	int			space_pressed;
	int			space_was_pressed;
	int			mouse_x;
	int			mouse_y;
	double		direction_vue;
	double		view_angle;

}				t_player;

typedef struct s_animate
{
	double		x;
	double		y;
	void		*frame[6];
	int			current_frame;
	int			frame_count;
	int			frame_ms;
	int			acc_ms;
	int			frame_width;
	int			frame_height;
}				t_animate;

typedef struct s_sprite_proj
{
	double		distance;
	int			screen_x;
	int			sprite_height;
	int			sprite_width;
}				t_sprite_proj;

typedef struct s_mlx_data
{
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_mlx_data;

typedef struct s_map
{
	char		**map;
	char		**tmp_map;
	int			player_x;
	int			player_y;
	int			y;
	int			x;
	int			width;
	int			height;
	int			total_size;
	t_animate	**sprites;
	int			sprite_count;
	t_animate	*s_animate;
	int			door_pos_x;
	int			door_pos_y;
	int			door_distance;
	t_player	*player;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		*no_text;
	char		*so_text;
	char		*we_text;
	char		*ea_text;
	char		*f_text;
	char		*c_text;
	char		*door_text;
	int			player_tile_x;
	int			player_tile_y;
	int			*c_rgb;
	int			*f_rgb;
	int			*nbr_text;
	int			nbr_line;
	int			fd;
	int			flag_players;
	int			door_open;
	char		*av;
	t_player	*player;
	t_minimap	*minimap;
	t_img		*img;
	t_map		*map;
	t_animate	*animate;
	t_texture	*textures;
}				t_game;

/************************************************************************
 *									CLEAN								*
 ***********************************************************************/
// cleaner_utils.c
void			free_texture_in_game(t_game *game);
void			free_all_sprites(t_game *game, t_map *map);
void			free_map_array(t_map *map);
void			free_struct(t_game *game);

// cleaner.c
void			free_all(t_game *game);
void			free_map(t_map *map);
int				cleanup(t_game *game);

/************************************************************************
 *								INITIALISATION							*
 ***********************************************************************/
// init_struct_cub3d.c
void			player_init(t_player **player, t_game *game);
void			map_init(t_map **map);
void			minimap_init(t_minimap **minimap);
void			animate_init(t_animate **animate);
void			game_init(t_game **game);

// intit_struct_game.c
void			text_init(t_texture **text);
void			img_init(t_img **img, t_game *game);
void			init_ray_params(t_ray_params *params);
int				load_textures(t_game *game);

// check_texture.c
int				check_texture_file(char *path);
int				validate_all_textures(t_game *game);

// init_textures.c
int				grab_we_text(t_game *game, char *line, int i);
int				grab_ea_text(t_game *game, char *line, int i);
int				grab_f_text(t_game *game, char *line, int i);
int				grab_c_text(t_game *game, char *line, int i);
int				load_single_texture(t_game *game, char *path, void **img,
					char **data);

// init.c
void			game_init(t_game **game);
void			map_init(t_map **map);
void			img_init(t_img **img, t_game *game);
void			player_init(t_player **player, t_game *game);
void			text_init(t_texture **text);
void			init_ray_params(t_ray_params *params);
int				init_mlx(t_game *game, t_map *map, t_img *img);

/************************************************************************
 *								PARSING									*
 ***********************************************************************/
// floodfill.c
void			free_tmp_map(t_map *map);
int				alloc_tmp_map(t_map *map);
void			fill(t_map *map, int x, int y);
int				flood_fill(t_map *map);

// map_copy_utils.c
void			map_copy(t_map *map, char *line);
int				get_greater_width(char *av);
int				get_map_height(char *av);
void			store_player_position(t_map *map, char c);
t_animate		**copy_sprites_array(t_map *map);

// map_copy.c
void			read_from_map(t_game *game, t_map *map, char *av);

// parsing_identifiers.c
int				check_id(t_game *game, char *line);
int				parse_identifiers_line(t_game *game, char *line);

// parsing_map.c
int				parse_map_line(t_game *game, char *line);

// parsing_param.c
int				check_arg_param(char **av);
int				check_cub_file(t_game *game, char *av);
int				check_colors_param(t_game *game);

// parsing.c
int				detector_start_map(char *line);
int				parsing(t_game *game, char *av);

// cleaner.c
void			free_map_array(t_map *map);

/************************************************************************
 *								ANIMATE									*
 ***********************************************************************/
// animate.c
int				load_sprite(t_game *game, t_animate *animate);
void			update_sprite_animation(t_animate *animate, int delta_ms);

// draw_sprite.c
void			draw_sprite_3d(t_game *game, t_img *img, t_animate *animate);

// draw_sprite_utils.c
int				is_transparent(int rgb);
int				get_sprite_pixel(void *img, int pos[2], t_animate *animate);

/************************************************************************
 *								UTILS									*
 ***********************************************************************/
// utils.c
void			ft_error(t_game *game, char *s);
int				ft_gnlen(char *gnl);

#endif