/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:44:23 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/30 11:03:44 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// void	draw_wall(t_img *img, int x, double wall_size, double angle)
// {
// 	int	y;

// 	y = 0;
// 	img->wall_start = (img->height / 2) - (wall_size / 2);
// 	img->wall_end = (img->height / 2) + (wall_size / 2);
// 	while (y < img->height)
// 	{
// 		if (y < img->wall_start)
// 			my_put_pixel(img, x, y, 0xE11E00);
// 		else if (y < img->wall_end)
// 			draw_wall_text(img, x, y, angle);
// 		else
// 			my_put_pixel(img, x, y, 0xDC6400);
// 		y++;
// 	}
// }
