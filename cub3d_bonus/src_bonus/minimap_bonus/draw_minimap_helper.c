/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: autret <autret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:00:00 by autret            #+#    #+#             */
/*   Updated: 2026/02/05 17:01:49 by autret           ###   ########.fr       */
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

t_minimap_pos	calc_minimap_pos(double x, double y, int tile_size)
{
	t_minimap_pos	pos;

	pos.minimap_x = MINIMAP_OFFSET + (x * tile_size) / TILE_SIZE;
	pos.minimap_y = MINIMAP_OFFSET + (y * tile_size) / TILE_SIZE;
	return (pos);
}

int	is_in_minimap(t_minimap_pos pos)
{
	return (pos.minimap_x >= MINIMAP_OFFSET
		&& pos.minimap_x < MINIMAP_OFFSET + MINIMAP_SIZE
		&& pos.minimap_y >= MINIMAP_OFFSET
		&& pos.minimap_y < MINIMAP_OFFSET + MINIMAP_SIZE);
}

void	draw_ray_pixel(t_img *img, double cx, double cy, int tile_size)
{
	t_minimap_pos	pos;

	pos = calc_minimap_pos(cx, cy, tile_size);
	if (is_in_minimap(pos))
		my_put_pixel(img, pos.minimap_x, pos.minimap_y, 0xFFFFFFFF);
}
