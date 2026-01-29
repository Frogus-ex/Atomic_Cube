/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:13:10 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/29 10:54:01 by tlorette         ###   ########.fr       */
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
# include "mlx.h"
# include <fcntl.h>
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
	double		direction_vue;
	double		view_angle;

}				t_player;

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
	int			*c_text_rgb;
	int			*f_text_rgb;
	int			*nbr_text;
	int			nbr_line;
	int			fd;
	int			flag_players;
	t_player	*player;
	t_img		*img;
	t_map		*map;
	t_texture	*textures;
}				t_game;

/************************************************************************
 *									CLEAN								*
 ***********************************************************************/
// cleaner.c
void			free_map_array(t_map *map);
void			free_all(t_game *game);
void			free_map(t_map *map);
int				cleanup(t_game *game);

/************************************************************************
 *								INITIALISATION							*
 ***********************************************************************/
// init_textures.c
void			grab_we_text(t_game *game, char *line, int i);
void			grab_ea_text(t_game *game, char *line, int i);
void			grab_f_text(t_game *game, char *line, int i);
void			grab_c_text(t_game *game, char *line, int i);
void			load_textures(t_game *game);

// init.c
void			game_init(t_game **game);
void			map_init(t_map **map);
void			img_init(t_img **img, t_game *game);
void			player_init(t_player **player, t_game *game);
void			text_init(t_texture **text);
void			init_mlx(t_game *game, t_map *map, t_img *img);

/************************************************************************
 *								PARSING									*
 ***********************************************************************/
// floodfill.c
void			free_tmp_map(t_map *map);
int				alloc_tmp_map(t_map *map);
void			tmp_map_copy(t_map *map, char *line);
void			fill(t_map *map, int x, int y);
int				flood_fill(t_game *game, t_map *map);

// map_copy.c
void			read_from_map(t_game *game, t_map *map, char *av);
int				get_map_height(char *av);
int				get_greater_width(char *av);
void			map_alloc(t_map *map, char *av);
void			map_copy(t_map *map, char *line);

// parsing_identifiers.c
int				check_id(t_game *game, char *line);
int				parse_identifiers_line(t_game *game, char *line);

// parsing_map.c
int				parse_map_line(t_game *game, char *line);

// parsing_param.c
void			check_arg_param(int ac, char **av);
int				check_cub_file(t_game *game, char *av);
int				check_colors_param(t_game *game);

// parsing.c
int				detector_start_map(char *line);
int				parsing(t_game *game, char *av);

// cleaner.c
void			free_map_array(t_map *map);

/************************************************************************
 *								UTILS									*
 ***********************************************************************/
// utils.c
void			ft_error(t_game *game, char *s);
int				ft_gnlen(char *gnl);
#endif