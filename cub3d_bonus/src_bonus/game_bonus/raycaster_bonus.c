/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:51:15 by aautret           #+#    #+#             */
/*   Updated: 2026/01/29 11:49:29 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	set_wall_dir(t_texture *texture, double ray_angle, int is_horiz)
{
	if (is_horiz)
	{
		if (sin(ray_angle) > 0)
			texture->side = 0;
		else
			texture->side = 1;
	}
	else
	{
		if (cos(ray_angle) > 0)
			texture->side = 0;
		else
			texture->side = 1;
	}
}

/**
 * @brief Lance deux rayons H + V et garde le plus proche
 * 
 * - normalise
 * 
 * @param img 
 * @param params 
 * @param ray_angle 
 */
void	get_wall_hit_dda(t_img *img, t_ray_params *params, double ray_angle)
{
	if (params->is_horizontal)
	{
		img->texture->side = 1;
		img->ray_dir_y = sin(ray_angle);
		img->texture->wall_x = fmod(params->ray_hit_x, TILE_SIZE) / TILE_SIZE;
	}
	else
	{
		img->texture->side = 0;
		img->ray_dir_x = cos(ray_angle);
		img->texture->wall_x = fmod(params->ray_hit_y, TILE_SIZE) / TILE_SIZE;
	}
}

void	get_distance_dda(t_img *img, t_ray_params *params, double ray_angle)
{
	double	corrected_distance;

	img->wall_distance = params->distance;
	corrected_distance = img->wall_distance * cos(ray_angle - img->player->direction_vue);
	if (corrected_distance <= 0.1)
		corrected_distance = 0.1;
	img->wall_size = (SCREEN_HEIGHT / corrected_distance) * TILE_SIZE;
}

void	cast_ray_dda(t_img *img, double ray_angle, int column)
{
	t_ray_params	horiz;
	t_ray_params	vert;
	double			horiz_dist;
	double			vert_dist;

	init_ray_params(&horiz);
	init_ray_params(&vert);
	setup_vertical_ray(img, ray_angle, &vert);
	vert_dist = cast_ray(img, &vert);
	setup_horizontal_ray(img, ray_angle, &horiz);
	horiz_dist = cast_ray(img, &horiz);
	if (horiz_dist < vert_dist)
	{
		horiz.distance = horiz_dist;
		horiz.is_horizontal = 1;
		get_wall_hit_dda(img, &horiz, ray_angle);
		get_distance_dda(img, &horiz, ray_angle);
	}
	else
	{
		vert.distance = vert_dist;
		vert.is_horizontal = 0;
		get_wall_hit_dda(img, &vert, ray_angle);
		get_distance_dda(img, &vert, ray_angle);
	}
	draw_wall(img, column, img->wall_size, ray_angle);
}
