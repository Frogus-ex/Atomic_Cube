/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:19:28 by aautret           #+#    #+#             */
/*   Updated: 2026/02/06 13:28:15 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

/**
 * @brief Trace un rayon sur la mini-map pour un angle absolu.
 * @param img image cible
 * @param angle angle du rayon en radians
 * @param tile_size taille de tuile calculée
 */
static void	draw_angle_new(t_img *img, double angle, int tile_size)
{
	double	current[2];
	double	step[2];
	int		i;

	if (!img || !img->player)
		return ;
	step[0] = cos(angle);
	step[1] = sin(angle);
	current[0] = img->player->origin_x;
	current[1] = img->player->origin_y;
	i = 0;
	while (i < 1000)
	{
		current[0] += step[0];
		current[1] += step[1];
		if (!check_colision(img, current[0], current[1]))
			break ;
		draw_ray_pixel(img, current[0], current[1], tile_size);
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

static void	draw_map_tiles(t_map *map, t_img *img, int tile_size)
{
	int	pos[2];
	int	color;

	pos[1] = 0;
	while (pos[1] < map->height)
	{
		pos[0] = 0;
		while (pos[0] < map->width)
		{
			if (map->map[pos[1]] && map->map[pos[1]][pos[0]])
			{
				color = get_tile_color(map->map[pos[1]][pos[0]]);
				draw_tile(img, pos, color, tile_size);
			}
			pos[0]++;
		}
		pos[1]++;
	}
}

/**
 * @brief Redessine la mini-carte (tuiles, joueur, rayons) et affiche la frame.
 * @param map representation grille
 * @param img image cible
 */
void	draw_minimap(t_map *map, t_img *img)
{
	int	tile_size;

	tile_size = calculate_tile_size(map);
	draw_map_tiles(map, img, tile_size);
	calc_and_draw_angle(img, tile_size);
}
