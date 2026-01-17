/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:07:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/21 10:52:33 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# define NUM_RAY 100

# include "cub3D.h"

typedef struct s_game	t_game;
typedef struct s_map	t_map;
typedef struct s_player	t_player;

typedef struct s_img
{
	void				*img;
	char				*addr;
	int					screen_width;
	int					screen_height;
	int					width;
	int					height;
	int					bits_per_pixel;
	int					endian;
	int					line_length;
	double				distance_x;
	double				distance_y;
	t_game				*game;
	t_map				*map;
	t_player			*player;
}						t_img;

/************************************************************************
 *									GRAPHIC								*
 ***********************************************************************/
// draw_map_util.c
int						calc_height(t_img *img);
void					draw_adjacent(t_img *img);
void					draw_negative_height(t_img *img);
void					draw_positive_height(t_img *img);

// draw_map.c
void					my_put_pixel(t_img *img, int x, int y, int color);
void					draw_initial_dot(t_img *img);
void					make_pixel(t_map *map, t_img *img);
void					draw_map(t_img *img, int x, int y, int color);
void					calc_and_draw_angle(t_img *img);

// init_vison.c
void					get_distance(t_img *img);

// key_handle.c
int						cleanup(t_game *game);
int						cross_close(t_game *game);
int						player_input(int keycode, t_img *img);
void					player_moves(t_img *img, int new_y, int new_x);

#endif