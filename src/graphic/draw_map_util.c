/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:54:58 by aautret           #+#    #+#             */
/*   Updated: 2026/01/15 17:34:20 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Calcule la hauteur des triangles rectangles (mini-map)
 * 
 * @param img 
 * @return int 
 */
int	calc_height(t_img *img)
{
	double	height;

	if (!img || !img->player)
		return (0);
	img->player->view_angle = (-M_PI / 8);
	img->distance_x = img->player->origin_x + 100
		* cos(img->player->view_angle);
	img->distance_y = img->player->origin_y + 100
		* sin(img->player->view_angle);
	height = fabs(img->distance_y - img->player->origin_y);
	return ((unsigned int)height);
}

/**
 * @brief Affiche le segment adjacent des triangles rectangles 
 * (segment partage par les deux triangles) (mini-map)
 * 
 * @param img 
 */
void	draw_adjacent(t_img *img)
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
	img->distance_y = img->player->origin_y + 100
		* sin(img->player->view_angle);
	step_x = (img->distance_x - img->player->origin_x) / ADJACENT;
	step_y = (img->distance_y - img->player->origin_y) / ADJACENT;
	i = 0;
	while (i < ADJACENT)
	{
		current_x = img->player->origin_x + 9 + step_x * i;
		current_y = img->player->origin_y + 9;
		my_put_pixel(img, (int)current_x, (int)current_y, 0xFFFF00);
		i++;
	}
}

/**
 * @brief Dessine la hauteur du triange restangle du "haut" (mini-map)
 * 
 * @param img 
 */
void	draw_negative_height(t_img *img)
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
	step_x = (img->distance_x - img->player->origin_x) / ADJACENT;
	step_y = (img->distance_y - img->player->origin_y) / ADJACENT;
	i = 0;
	while (i < ADJACENT)
	{
		current_x = img->player->origin_x + ADJACENT;
		current_y = img->player->origin_y + 9 + step_y * i;
		my_put_pixel(img, (int)current_x, (int)current_y, 0xFFFF00);
		i++;
	}
}

/**
 * @brief Dessine la hauteur du triange restangle du "bas" (mini-map)
 * 
 * @param img 
 */
void	draw_positive_height(t_img *img)
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
	step_x = (img->distance_x - img->player->origin_x) / ADJACENT;
	step_y = (img->distance_y - img->player->origin_y) / ADJACENT;
	i = 0;
	while (i < ADJACENT)
	{
		current_x = img->player->origin_x + ADJACENT;
		current_y = img->player->origin_y + 9 - step_y * i;
		my_put_pixel(img, (int)current_x, (int)current_y, 0xFFFF00);
		i++;
	}
}