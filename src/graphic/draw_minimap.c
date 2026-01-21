/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:56:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/21 10:59:09 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Trace un rayon sur la mini-map pour un angle absolu.
 * @param img image cible
 * @param angle angle du rayon en radians
 */
static void	draw_angle_new(t_img *img, double angle)
{
	double	step_x;
	double	step_y;
	double	current_x;
	double	current_y;
	int		i;

	if (!img || !img->player)
		return ;
	img->player->view_angle = img->player->direction_vue + (-M_PI / 8);
	img->distance_x = img->player->origin_x + 110 * cos(angle);
	img->distance_y = img->player->origin_y + 110 * sin(angle);
	step_x = (img->distance_x - img->player->origin_x) / 110;
	step_y = (img->distance_y - img->player->origin_y) / 110;
	i = 0;
	while (i < ADJACENT)
	{
		current_x = img->player->origin_x + step_x * i;
		current_y = img->player->origin_y + step_y * i;
		my_put_pixel(img, current_x, current_y, 0xFFFF00);
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
	angle_step = (M_PI / 4) / img->screen_width;
	while (i < img->screen_width)
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
	while (py < TILE_SIZE)
	{
		px = 0;
		while (px < TILE_SIZE)
		{
			my_put_pixel(img, x * TILE_SIZE + px, y * TILE_SIZE + py, color);
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
	draw_player_circle(img, img->player->origin_x, img->player->origin_y,
		TILE_SIZE / 4);
	calc_and_draw_angle(img);
	mlx_put_image_to_window(img->game->mlx, img->game->win, img->img, 0, 0);
}
