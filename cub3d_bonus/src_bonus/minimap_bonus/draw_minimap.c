/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:19:28 by aautret           #+#    #+#             */
/*   Updated: 2026/02/06 14:20:20 by aautret          ###   ########.fr       */
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
	int	pos[2]; //position dans la minimap
	int	map_pos[2]; //position dans la VRAIE map
	int	visible[2]; //nombre de cases visible
	int start[2]; //case de depart
	int	color;
	
	visible[0] = MINIMAP_WIDTH / tile_size; //visible en x
	visible[1] = MINIMAP_HEIGHT / tile_size; //visible en y
	start[0] = (int)(img->player->origin_x / TILE_SIZE) - (visible[0] / 2);
	start[1] = (int)(img->player->origin_y / TILE_SIZE) - (visible[1] / 2);
	pos[1] = 0;
	while (pos[1] < visible[1])
	{
		pos[0] = 0;
		while (pos[0] < visible[0])
		{
			//convert pos minimap into map
			map_pos[0] = start[0] + pos[0];
			map_pos[1] = start[1] + pos[1];
			//verifier si on est dans la map
			if (map_pos[1] >= 0)
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



// static void	draw_map_tiles(t_map *map, t_img *img, int tile_size)
// {
//     int	pos[2];           // Position dans la MINIMAP (0 à visible_tiles)
//     int	map_pos[2];       // Position dans la VRAIE MAP
//     int	visible[2];       // Nombre de cases visibles
//     int	start[2];         // Case de départ (coin haut-gauche de la fenêtre)
//     int	color;

//     // 1. Calculer combien de cases on peut afficher
//     visible[0] = MAX_MINIMAP_WIDTH / tile_size;   // Cases visibles en X
//     visible[1] = MAX_MINIMAP_HEIGHT / tile_size;  // Cases visibles en Y

//     // 2. Centrer la fenêtre sur le joueur
//     start[0] = (int)(img->player->origin_x / TILE_SIZE) - (visible[0] / 2);
//     start[1] = (int)(img->player->origin_y / TILE_SIZE) - (visible[1] / 2);

//     // 3. Parcourir la fenêtre visible (pas toute la map)
//     pos[1] = 0;
//     while (pos[1] < visible[1])
//     {
//         pos[0] = 0;
//         while (pos[0] < visible[1])
//         {
//             // 4. Convertir la position minimap → position map
//             map_pos[0] = start[0] + pos[0];
//             map_pos[1] = start[1] + pos[1];

//             // 5. Vérifier si on est dans la carte
//             if (map_pos[1] >= 0 && map_pos[1] < map->height &&
//                 map_pos[0] >= 0 && map_pos[0] < map->width &&
//                 map->map[map_pos[1]] && map->map[map_pos[1]][map_pos[0]])
//             {
//                 // Case valide : afficher la vraie couleur
//                 color = get_tile_color(map->map[map_pos[1]][map_pos[0]]);
//                 draw_tile(img, pos, color, tile_size);
//             }
//             else
//             {
//                 // Hors de la carte : afficher du gris foncé
//                 draw_tile(img, pos, 0x333333, tile_size);
//             }
//             pos[0]++;
//         }
//         pos[1]++;
//     }
// }