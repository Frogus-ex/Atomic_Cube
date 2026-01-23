/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:07:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/23 13:26:07 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

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
	double				wall_distance;
	double				wall_size;
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

// draw_minimap.c
void					draw_minimap(t_map *map, t_img *img);

// graphic_utils.c
void					my_put_pixel(t_img *img, int x, int y, int color);
int						cleanup(t_game *game);
int						cross_close(t_game *game);
int						find_biggest(t_img *img);

// init_vison.c
void					get_distance(t_img *img, double xm, double ym,
							double angle);

// key_handle.c
int						player_input(int keycode, t_img *img);
void					player_moves(t_img *img, int new_y, int new_x);

// draw_cub3d.c
void					draw_wall(t_img *img, int x, double wall_size);

#endif