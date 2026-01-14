/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:56:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/14 18:33:35 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	my_put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	*(int *)(img->addr + offset) = color;
}

void	draw_initial_dot(t_img *img)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	while (i < img->height * img->line_length)
	{
		*(int *)(img->addr + i) = 0x000000;
		i += (img->bits_per_pixel / 8);
	}
	y = img->player->y;
	while (y < img->player->y + 18)
	{
		x = img->player->x;
		while (x < (img->player->x + 18))
		{
			my_put_pixel(img, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
	draw_negative_angle(img);
	draw_positive_angle(img);
	mlx_put_image_to_window(img->game->mlx, img->game->win, img->img, 0, 0);
}

void	draw_negative_angle(t_img *img)
{
	double	step_x;
	double	step_y;
	double	current_x;
	double	current_y;
	double	distance;
	int		i;

	if (!img || !img->player)
		return ;
	img->player->view_angle = -M_PI / 4;
	img->distance_x = img->player->x + 100 * cos(img->player->view_angle);
	img->distance_y = img->player->y + 100 * sin(img->player->view_angle);
	distance = 100;
	step_x = (img->distance_x - img->player->x) / distance;
	step_y = (img->distance_y - img->player->y) / distance;
	i = 0;
	while (i < (int)distance)
	{
		current_x = img->player->x + 9 + step_x * i;
		current_y = img->player->y + 9 + step_y * i;
		my_put_pixel(img, (int)current_x, (int)current_y, 0xFFFF00);
		i++;
	}
}

void	draw_positive_angle(t_img *img)
{
	double	step_x;
	double	step_y;
	double	current_x;
	double	current_y;
	double	distance;
	int		i;

	if (!img || !img->player)
		return ;
	img->player->view_angle = M_PI / 4;
	img->distance_x = img->player->x + 100 * cos(img->player->view_angle);
	img->distance_y = img->player->y + 100 * sin(img->player->view_angle);
	distance = 100;
	step_x = (img->distance_x - img->player->x) / distance;
	step_y = (img->distance_y - img->player->y) / distance;
	i = 0;
	while (i < (int)distance)
	{
		current_x = img->player->x + 9 + step_x * i;
		current_y = img->player->y + 9 + step_y * i;
		my_put_pixel(img, (int)current_x, (int)current_y, 0xFFFF00);
		i++;
	}
}
