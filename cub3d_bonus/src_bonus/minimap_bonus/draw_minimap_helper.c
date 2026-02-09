/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:00:00 by autret            #+#    #+#             */
/*   Updated: 2026/02/09 15:13:23 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

int	get_tile_color(char cell)
{
	if (cell == '1')
		return (0xFF0000);
	else if (cell == 'D')
		return (0x654321);
	else
		return (0x000000);
}

t_minimap_pos	calc_minimap_pos(t_img *img, double x, double y, int tile_size)
{
	t_minimap_pos	pos;
	double			world_dx;
	double			world_dy;

	world_dx = x - img->player->origin_x;
	world_dy = y - img->player->origin_y;
	pos.minimap_x = MINIMAP_OFFSET + MINIMAP_WIDTH / 2 + (int)((world_dx
				* tile_size) / TILE_SIZE);
	pos.minimap_y = MINIMAP_OFFSET + MINIMAP_HEIGHT / 2 + (int)((world_dy
				* tile_size) / TILE_SIZE);
	return (pos);
}

int	is_in_minimap(t_minimap_pos pos)
{
	return (pos.minimap_x >= MINIMAP_OFFSET && pos.minimap_x < MINIMAP_OFFSET
		+ MINIMAP_WIDTH && pos.minimap_y >= MINIMAP_OFFSET
		&& pos.minimap_y < MINIMAP_OFFSET + MINIMAP_HEIGHT);
}

void	draw_ray_pixel(t_img *img, double cx, double cy, int tile_size)
{
	t_minimap_pos	pos;

	pos = calc_minimap_pos(img, cx, cy, tile_size);
	if (is_in_minimap(pos))
		my_put_pixel(img, pos.minimap_x, pos.minimap_y, 0xFFFFFFFF);
}

void	draw_one_tile(t_img *img, int tile_size, int map_pos[2], int pos[2])
{
	int	color;
	int	x;
	int	y;

	x = map_pos[0];
	y = map_pos[1];
	if (y < 0 || y >= img->map->height || x < 0 || x >= img->map->width
		|| !img->map->map[y] || !img->map->map[y][x])
		draw_tile(img, pos, 0x000000, tile_size);
	else
	{
		color = get_tile_color(img->map->map[y][x]);
		draw_tile(img, pos, color, tile_size);
	}
}
