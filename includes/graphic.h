/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:07:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/13 17:54:30 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include "cub3D.h"

typedef struct s_game	t_game;
typedef struct s_map	t_map;

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
	void				*player;
	void				*floor;
	void				*wall;
	t_game				*game;
	t_map				*map;
}						t_img;

void					init_mlx(t_game *game, t_map *map, t_img *img);
void					load_texture(t_game *game, t_img *img);
void					if_draw(t_img *img, int y, int x);
void					draw_map(t_img *img);

#endif