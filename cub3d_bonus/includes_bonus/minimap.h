/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:23:38 by aautret           #+#    #+#             */
/*   Updated: 2026/02/09 15:11:07 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3D.h"

typedef struct s_game	t_game;
typedef struct s_map	t_map;
typedef struct s_player	t_player;

typedef struct s_minimap
{
	int					player_pos_x;
	int					player_pos_y;
}						t_minimap;

typedef struct s_minimap_pos
{
	int					minimap_x;
	int					minimap_y;
}						t_minimap_pos;

/************************************************************************
 *								MINIMAP									*
 ***********************************************************************/

// draw_minimap.c
void					draw_minimap(t_map *map, t_img *img);

// draw_minimap_helper.c
int						get_tile_color(char cell);
t_minimap_pos			calc_minimap_pos(t_img *img, double x, double y,
							int tile_size);
int						is_in_minimap(t_minimap_pos pos);
void					draw_ray_pixel(t_img *img, double cx, double cy,
							int tile_size);
void					draw_one_tile(t_img *img, int tile_size, int map_pos[2],
							int pos[2]);

// draw_minimap_utils.c
int						calculate_tile_size(t_map *map);
int						check_colision(t_img *img, double px, double py);
void					draw_player_circle(t_img *img, int cx, int cy,
							int radius);
void					draw_tile(t_img *img, int pos[2], int color,
							int tile_size);

#endif