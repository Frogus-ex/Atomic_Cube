/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: autret <autret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:38:14 by autret            #+#    #+#             */
/*   Updated: 2026/02/05 17:09:02 by autret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

int	calculate_tile_size(t_map *map)
{
	int	tile_width;
	int	tile_height;

	tile_width = MINIMAP_SIZE / map->width;
	tile_height = MINIMAP_SIZE / map->height;
	if (tile_width < tile_height)
		return (tile_width);
	return (tile_height);
}

int	check_colision(t_img *img, double px, double py)
{
	int		tx;
	int		ty;
	char	cell;

	if (!img || !img->map || !img->map->map || px < 0 || py < 0)
		return (0);
	tx = (int)floor(px / TILE_SIZE);
	ty = (int)floor(py / TILE_SIZE);
	if (ty < 0 || ty >= img->map->height || tx < 0 || tx >= img->map->width)
		return (0);
	if (!img->map->map[ty] || !img->map->map[ty][tx])
		return (0);
	cell = img->map->map[ty][tx];
	if (cell == '1' || cell == ' ')
		return (0);
	if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
		return (1);
	return (0);
}

static void	draw_circle_line(t_img *img, int cx, int cy, int params[2])
{
	int	xi;

	xi = cx - params[0];
	while (xi <= cx + params[0])
	{
		my_put_pixel(img, xi, cy + params[1], 0xFFFFFFFF);
		my_put_pixel(img, xi, cy - params[1], 0xFFFFFFFF);
		xi++;
	}
}

void	draw_player_circle(t_img *img, int cx, int cy, int radius)
{
	int	x;
	int	y;
	int	err;
	int	params[2];

	x = -radius;
	y = 0;
	err = 2 - 2 * radius;
	while (x <= 0)
	{
		params[0] = -x;
		params[1] = y;
		draw_circle_line(img, cx, cy, params);
		if (err <= y)
			err += ++y * 2 + 1;
		if (err > x || err > y)
			err += ++x * 2 + 1;
	}
}

void	draw_tile(t_img *img, int pos[2], int color, int tile_size)
{
	int	px;
	int	py;

	py = 0;
	while (py < tile_size)
	{
		px = 0;
		while (px < tile_size)
		{
			my_put_pixel(img, MINIMAP_OFFSET + pos[0] * tile_size + px,
				MINIMAP_OFFSET + pos[1] * tile_size + py, color);
			px++;
		}
		py++;
	}
}
