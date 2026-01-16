/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:56:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/16 16:05:05 by tlorette         ###   ########.fr       */
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
 * @brief Dessine un rayon à angle négatif depuis la position du joueur
 * (hypotenuse)
 *
 * @param img
 * @param j
 */
static void	draw_negative_angle(t_img *img, int j)
{
	double	step_x;
	double	step_y;
	double	current_x;
	double	current_y;
	int		i;

	if (!img || !img->player)
		return ;
	img->player->view_angle = (-M_PI / 8);
	img->distance_x = img->player->origin_x + 100
		* cos(img->player->view_angle);
	img->distance_y = img->player->origin_y + j + 100
		* sin(img->player->view_angle);
	step_x = (img->distance_x - img->player->origin_x) / ADJACENT;
	step_y = (img->distance_y - img->player->origin_y) / ADJACENT;
	i = 0;
	while (i < ADJACENT)
	{
		current_x = img->player->origin_x + 9 + step_x * i;
		current_y = img->player->origin_y + 9 + step_y * i;
		my_put_pixel(img, (int)current_x, (int)current_y, 0xFFFF00);
		i++;
	}
}

/**
 * @brief Dessine un rayona angle positif depuis a position du joueur
 * (hypotenus)
 *
 * @param img
 * @param j
 */
static void	draw_positive_angle(t_img *img, int j)
{
	double	step_x;
	double	step_y;
	double	current_x;
	double	current_y;
	int		i;

	if (!img || !img->player)
		return ;
	img->player->view_angle = (M_PI / 8);
	img->distance_x = img->player->origin_x + 100
		* cos(img->player->view_angle);
	img->distance_y = img->player->origin_y - j + 100
		* sin(img->player->view_angle);
	step_x = (img->distance_x - img->player->origin_x) / ADJACENT;
	step_y = (img->distance_y - img->player->origin_y) / ADJACENT;
	i = 0;
	while (i < ADJACENT)
	{
		current_x = img->player->origin_x + 9 + step_x * i;
		current_y = img->player->origin_y + 9 + step_y * i;
		my_put_pixel(img, (int)current_x, (int)current_y, 0xFFFF00);
		i++;
	}
}

/**
 * @brief Permet de dessiner tous les rayons de l'angle de vue sur la mini-map
 *
 * @param img
 */
static void	draw_angles(t_img *img)
{
	int	j;
	int	height_1;

	j = 0;
	height_1 = calc_height(img);
	while (j < height_1)
	{
		draw_negative_angle(img, j);
		draw_positive_angle(img, j);
		j++;
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
	int	i;

	i = 0;
	while (i < img->height * img->line_length)
	{
		*(int *)(img->addr + i) = 0x000000;
		i += (img->bits_per_pixel / 8);
	}
	y = img->player->origin_y;
	while (y < img->player->origin_y + 18)
	{
		x = img->player->origin_x;
		while (x < (img->player->origin_x + 18))
		{
			my_put_pixel(img, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
	draw_angles(img);
	mlx_put_image_to_window(img->game->mlx, img->game->win, img->img, 0, 0);
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
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(img->game->mlx, img->game->win, img->img, 0, 0);
}
