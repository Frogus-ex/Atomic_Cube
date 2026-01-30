/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:54:58 by aautret           #+#    #+#             */
/*   Updated: 2026/01/30 11:04:02 by aautret          ###   ########.fr       */
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
