/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:36:27 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/15 17:41:43 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Get the distance objectCalcule la position finale d'un rayon selon 
 * l'angle et la distance de vue du joueur
 * 
 * @param img 
 */
void	get_distance(t_img *img)
{
	if (!img || !img->player)
		return ;
	img->distance_x = img->player->origin_x + img->player->view_distance
		* cos(img->player->view_angle);
	img->distance_y = img->player->origin_y + img->player->view_distance
		* sin(img->player->view_angle);
}
