/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 00:00:00 by aautret           #+#    #+#             */
/*   Updated: 2026/02/03 14:18:03 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

double	norme_angle(double ray_angle)
{
	while (ray_angle < 0)
		ray_angle += 2 * M_PI;
	while (ray_angle >= 2 * M_PI)
		ray_angle -= 2 * M_PI;
	return (ray_angle);
}

/**
 * @brief Calcul ou le rayon va toucher les lignes horizontales de la grille 
 * 
 * - On determine si le rayon va vers le haut ou le bas
 * @param img 
 * @param ray_angle 
 * @param params 
 */
void	setup_horizontal_ray(t_img *img, double ray_angle, t_ray_params *params)
{
	double	tan_val;

	ray_angle = norme_angle(ray_angle);
	params->ray_hit_y = floor(img->player->origin_y / TILE_SIZE) * TILE_SIZE;
	if (sin(ray_angle) > 0)
	{
		params->ray_hit_y += TILE_SIZE;
		params->step_y = TILE_SIZE;
	}
	else
	{
		params->ray_hit_y -= 0.0001;
		params->step_y = -TILE_SIZE;
	}
	tan_val = tan(ray_angle);
	if (fabs(tan_val) < 0.0001)
		tan_val = 0.0001;
	params->ray_hit_x = img->player->origin_x + \
		(params->ray_hit_y - img->player->origin_y) / tan_val;
	params->step_x = TILE_SIZE / tan_val;
	if ((cos(ray_angle) < 0 && params->step_x > 0) \
		|| (cos(ray_angle) > 0 && params->step_x < 0))
		params->step_x = -params->step_x;
}

/**
 * @brief Calcul ou le rayon va toucher les lignes verticales de la grille
 * 
 * @param img 
 * @param ray_angle 
 * @param params 
 */
void	setup_vertical_ray(t_img *img, double ray_angle, t_ray_params *params)
{
	double	tan_val;

	ray_angle = norme_angle(ray_angle);
	params->ray_hit_x = floor(img->player->origin_x / TILE_SIZE) * TILE_SIZE;
	if (cos(ray_angle) > 0)
	{
		params->ray_hit_x += TILE_SIZE;
		params->step_x = TILE_SIZE;
	}
	else
	{
		params->ray_hit_x -= 0.0001;
		params->step_x = -TILE_SIZE;
	}
	tan_val = tan(ray_angle);
	params->ray_hit_y = img->player->origin_y + \
		(params->ray_hit_x - img->player->origin_x) * tan_val;
	params->step_y = TILE_SIZE * tan_val;
	if ((sin(ray_angle) < 0 && params->step_y > 0) \
		|| (sin(ray_angle) > 0 && params->step_y < 0))
		params->step_y = -params->step_y;
}

/**
 * @brief Trouve le premier mur, avance pas a pas sur la grille jusqu'a
 * trouver un mur
 * 
 * - convertit les coordonnees pixel en coor grille
 * - verifie si a chaque fois on est toujours dans la map
 * (si oui distance infinie pas de mur)
 * - check si c'es tun mur (si oui on arrete)
 * - sinon on avance au prochain pas
 * 
 * @param img 
 * @param params 
 * @return double 
 */
double	cast_ray(t_img *img, t_ray_params *params)
{
	while (!params->found_wall && !params->is_door)
	{
		params->map_x = (int)(params->ray_hit_x) / TILE_SIZE;
		params->map_y = (int)(params->ray_hit_y) / TILE_SIZE;
		if (params->map_x < 0 || params->map_x >= img->map->width \
			|| params->map_y < 0 || params->map_y >= img->map->height)
			break ;
		if (img->map->map[(int)params->map_y][(int)params->map_x] == '1')
			params->found_wall = 1;
		else if (img->map->map[(int)params->map_y][(int)params->map_x] == 'D')
			params->is_door = 1;
		else
		{
			params->ray_hit_x += params->step_x;
			params->ray_hit_y += params->step_y;
		}
	}
	return (sqrt(pow(params->ray_hit_x - img->player->origin_x, 2) + \
				pow(params->ray_hit_y - img->player->origin_y, 2)));
}
