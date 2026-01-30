/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:19:28 by aautret           #+#    #+#             */
/*   Updated: 2026/01/30 17:57:51 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

static int	calculate_tile_size(t_map *map)
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
	int	tx;
	int	ty;

	if (!img || !img->map || !img->map->map || px < 0 || py < 0)
		return (0);
	tx = (int)floor(px / TILE_SIZE);
	ty = (int)floor(py / TILE_SIZE);
	if (ty < 0 || ty >= img->map->height || tx < 0 || tx >= img->map->width)
		return (0);
	if (!img->map->map[ty] || !img->map->map[ty][tx])
		return (0);
	if (img->map->map[ty][tx] == '1')
		return (0);
	return (1);
}

/**
 * @brief Trace un rayon sur la mini-map pour un angle absolu.
 * @param img image cible
 * @param angle angle du rayon en radians
 * @param tile_size taille de tuile calculée
 */
static void	draw_angle_new(t_img *img, double angle, int tile_size)
{
	double	current_x;
	double	current_y;
	int		minimap_x;
	int		minimap_y;
	int		i;

	if (!img || !img->player)
		return ;
	i = 0;
	while (i < 1000)
	{
		current_x = img->player->origin_x + cos(angle) * i;
		current_y = img->player->origin_y + sin(angle) * i;
		if (!check_colision(img, current_x, current_y))
			break ;
		minimap_x = MINIMAP_OFFSET + (current_x * tile_size) / TILE_SIZE;
		minimap_y = MINIMAP_OFFSET + (current_y * tile_size) / TILE_SIZE;
		my_put_pixel(img, minimap_x, minimap_y, 0xFFFFFFFF);
		i++;
	}
}

/**
 * @brief Dessine les rayons depuis la position courante du joueur
 *
 * Calcule et affiche le faisceau de rayons autour de la direction vue.
 * @param img image cible
 * @param tile_size taille de tuile calculée
 */
static void	calc_and_draw_angle(t_img *img, int tile_size)
{
	double	angle_step;
	double	angle;
	int		i;

	i = 0;
	angle_step = (M_PI / 4) / 60;
	while (i < 60)
	{
		angle = img->player->direction_vue - (M_PI / 8) + (i * angle_step);
		draw_angle_new(img, angle, tile_size);
		i++;
	}
}

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
 * @brief Remplit une tuile (carre de tile_size) avec une couleur.
 * @param img image cible
 * @param x colonne de tuile
 * @param y ligne de tuile
 * @param color couleur ARGB
 * @param tile_size taille de tuile calculée
 */
static void	draw_map(t_img *img, int x, int y, int color, int tile_size)
{
	int	px;
	int	py;

	py = 0;
	while (py < tile_size)
	{
		px = 0;
		while (px < tile_size)
		{
			my_put_pixel(img, MINIMAP_OFFSET + x * tile_size + px,
				MINIMAP_OFFSET + y * tile_size + py, color);
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
	int	tile_size;

	tile_size = calculate_tile_size(map);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y] && map->map[y][x])
			{
				if (map->map[y][x] == '1')
					draw_map(img, x, y, 0xFF0000, tile_size);
				else
					draw_map(img, x, y, 0x000000, tile_size);
			}
			x++;
		}
		y++;
	}
	calc_and_draw_angle(img, tile_size);
	player_minimap_x = MINIMAP_OFFSET + (img->player->origin_x * tile_size)
		/ TILE_SIZE;
	player_minimap_y = MINIMAP_OFFSET + (img->player->origin_y * tile_size)
		/ TILE_SIZE;
	draw_player_circle(img, player_minimap_x, player_minimap_y, tile_size / 4);
}
