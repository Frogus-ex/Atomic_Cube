/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:19:28 by aautret           #+#    #+#             */
/*   Updated: 2026/01/30 13:42:56 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

static void	draw_player_circle(t_img *img, int cx, int cy, int radius)
{
	int	x;
	int	y;
	int	err;
	int	qx;
	int	xi;

	x = -radius;
	y = 0;
	err = 2 - 2 * radius;
	while (x <= 0)
	{
		qx = cx - x;
		xi = cx + x;
		while (xi <= qx)
		{
			my_put_pixel(img, xi, cy + y, 0xFFFFFFFF);
			my_put_pixel(img, xi, cy - y, 0xFFFFFFFF);
			xi++;
		}
		if (err <= y)
			err += ++y * 2 + 1;
		if (err > x || err > y)
			err += ++x * 2 + 1;
	}
}

/**
 * @brief Remplit une tuile (carre de TILE_SIZE) avec une couleur.
 * @param img image cible
 * @param x colonne de tuile
 * @param y ligne de tuile
 * @param color couleur ARGB
 */
static void	draw_map(t_img *img, int x, int y, int color)
{
	int	px;
	int	py;

	py = 0;
	while (py < TILE_SIZE_MINIMAP)
	{
		px = 0;
		while (px < TILE_SIZE_MINIMAP)
		{
			my_put_pixel(img, x * TILE_SIZE_MINIMAP + px, y * TILE_SIZE_MINIMAP
				+ py, color);
			px++;
		}
		py++;
	}
}

/**
 * @brief Redessine la mini-carte (tuiles, joueur, rayons) et affiche la frame.
 * @param map representation grille
 * @param img image cible
 */
void	draw_minimap(t_map *map, t_img *img)
{
	int	y;
	int	x;
	int	player_minimap_x;
	int	player_minimap_y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->map[y] && map->map[y][x])
			{
				if (map->map[y][x] == '1')
					draw_map(img, x, y, 0xFF0000);
				else
					draw_map(img, x, y, 0x000000);
			}
		}
	}
	player_minimap_x = (img->player->origin_x * TILE_SIZE_MINIMAP) / TILE_SIZE;
	player_minimap_y = (img->player->origin_y * TILE_SIZE_MINIMAP) / TILE_SIZE;
	draw_player_circle(img, player_minimap_x, player_minimap_y,
		TILE_SIZE_MINIMAP / 4);
}
