/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:56:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/19 10:39:23 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Place un pixel de couleur sur l'image aux coordonnees (x, y)
 *
 * @param img
 * @param x
 * @param y
 * @param color
 *
 * @param img
 * @param x
 * @param y
 * @param color
 */
void	my_put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	*(int *)(img->addr + offset) = color;
}

/**
 * @brief Dessine un rayon d'angle donnee
 *
 * @param img
 * @param angle
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
		current_x = img->player->origin_x + 9 + step_x * i;
		current_y = img->player->origin_y + 9 + step_y * i;
		my_put_pixel(img, current_x, current_y, 0xFFFF00);
		i++;
	}
}

/**
 * @brief Augmente l'angle du rayon afficher au fur et a mesure
 *
 * @param img
 */
void	calc_and_draw_angle(t_img *img)
{
	double	angle_step;
	double	angle;
	int		i;

	i = 0;
	angle_step = (M_PI / 4) / NUM_RAY;
	while (i < NUM_RAY)
	{
		angle = img->player->direction_vue - (M_PI / 8) + (i
				* angle_step);
		draw_angle_new(img, angle);
		i++;
	}
}

/**
 * @brief Dessine le point initial du joueur et les rayons sur la mini-map
 *
 * @param img
 */
void	draw_initial_dot(t_img *img)
{
	int	x;
	int	y;

	y = img->map->player_y;
	while (y)
	{
		x = img->map->player_x;
		while (x)
		{
			my_put_pixel(img, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
	calc_and_draw_angle(img);
}

void	draw_map(t_img *img, int x, int y, int color)
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

void	make_pixel(t_map *map, t_img *img)
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
				else if (map->map[y][x] == '0')
					draw_map(img, x, y, 0x000000);
				else if (map->map[y][x] == 'N')
					draw_map(img, x, y, 0xFFFFFF);
				draw_angles(img);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(img->game->mlx, img->game->win, img->img, 0, 0);
}
