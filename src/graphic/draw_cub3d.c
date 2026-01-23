/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:44:23 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/23 14:07:01 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_wall(t_img *img, int x, double wall_size)
{
	double	wall_start;
	double	wall_end;
	int		y;

	y = 0;
	wall_start = (img->height / 2) - (wall_size / 2);
	wall_end = (img->height / 2) + (wall_size / 2);
	while (y < img->height)
	{
		if (y < wall_start)
			my_put_pixel(img, x, y, 0xE11E00);
		else if (y < wall_end)
			my_put_pixel(img, x, y, 0xDC6400);
		else
			my_put_pixel(img, x, y, 0xFFFF00);
		y++;
	}
}
