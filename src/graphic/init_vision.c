/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:36:27 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/15 15:00:19 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	get_distance(t_img *img)
{
	if (!img || !img->player)
		return ;
	img->distance_x = img->player->origin_x + img->player->view_distance
		* cos(img->player->view_angle);
	img->distance_y = img->player->origin_y + img->player->view_distance
		* sin(img->player->view_angle);
}
