/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:36:27 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/14 18:32:50 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	get_distance(t_img *img)
{
	if (!img || !img->player)
		return ;
	img->distance_x = img->player->x + img->player->view_distance
		* cos(img->player->view_angle);
	img->distance_y = img->player->y + img->player->view_distance
		* sin(img->player->view_angle);
}

void	reset_img_distance(t_img *img)
{
	img->distance_x = 0;
	img->distance_y = 0;
}
