/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: autret <autret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:19:28 by aautret           #+#    #+#             */
/*   Updated: 2026/02/06 19:01:16 by autret           ###   ########.fr       */
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

/**
 * @brief Dessine la partie de la map autour du joueur dans la minimap
 *
 * - Calcul combien de cases on peut afficher
 *
 * - Centrer la fenetre sur le joueur
 *
 * @param map
 * @param img
 * @param tile_size
 */
static void	draw_map_tiles(t_map *map, t_img *img, int tile_size)
{
	int	pos[2];
	int	map_pos[2];
	int	visible[2];
	int	start[2];
	int	color;

	visible[0] = MINIMAP_WIDTH / tile_size;
	visible[1] = MINIMAP_HEIGHT / tile_size;
	start[0] = (int)(img->player->origin_x / TILE_SIZE) - (visible[0] / 2);
	start[1] = (int)(img->player->origin_y / TILE_SIZE) - (visible[1] / 2);
	pos[1] = 0;
	while (pos[1] < visible[1])
	{
		pos[0] = 0;
		while (pos[0] < visible[0])
		{
			map_pos[0] = start[0] + pos[0];
			map_pos[1] = start[1] + pos[1];
			if (map_pos[1] >= 0 && map_pos[1] < map->height
				&& map_pos[0] >= 0 && map_pos[0] < map->width
				&& map->map[map_pos[1]] && map->map[map_pos[1]][map_pos[0]])
			{
				color = get_tile_color(map->map[map_pos[1]][map_pos[0]]);
				draw_tile(img, pos, color, tile_size);
			}
			else
				draw_tile(img, pos, 0x000000, tile_size);
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
	int	center_x;
	int	center_y;

	tile_size = calculate_tile_size(map);
	draw_map_tiles(map, img, tile_size);
	calc_and_draw_angle(img, tile_size);
	center_x = MINIMAP_OFFSET + MINIMAP_WIDTH / 2;
	center_y = MINIMAP_OFFSET + MINIMAP_HEIGHT / 2;
	draw_player_circle(img, center_x, center_y, 3);
}
