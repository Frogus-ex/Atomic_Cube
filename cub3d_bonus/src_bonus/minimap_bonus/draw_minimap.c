/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:19:28 by aautret           #+#    #+#             */
/*   Updated: 2026/01/30 17:38:21 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

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
 */
static void	draw_angle_new(t_img *img, double angle)
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
		minimap_x = (current_x * TILE_SIZE_MINIMAP) / TILE_SIZE;
		minimap_y = (current_y * TILE_SIZE_MINIMAP) / TILE_SIZE;
		my_put_pixel(img, minimap_x, minimap_y, 0xFFFFFFFF);
		i++;
	}
}

/**
 * @brief Dessine les rayons depuis la position courante du joueur
 *
 * Calcule et affiche le faisceau de rayons autour de la direction vue.
 * @param img image cible
 */
static void	calc_and_draw_angle(t_img *img)
{
	double	angle_step;
	double	angle;
	int		i;

	i = 0;
	angle_step = (M_PI / 4) / 60;
	while (i < 60)
	{
		angle = img->player->direction_vue - (M_PI / 8) + (i * angle_step);
		draw_angle_new(img, angle);
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

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y] && map->map[y][x])
			{
				if (map->map[y][x] == '1')
					draw_map(img, x, y, 0xFF0000);
				else
					draw_map(img, x, y, 0x000000);
			}
			x++;
		}
		y++;
	}
	calc_and_draw_angle(img);
	player_minimap_x = (img->player->origin_x * TILE_SIZE_MINIMAP) / TILE_SIZE;
	player_minimap_y = (img->player->origin_y * TILE_SIZE_MINIMAP) / TILE_SIZE;
	draw_player_circle(img, player_minimap_x, player_minimap_y,
		TILE_SIZE_MINIMAP / 4);
}
