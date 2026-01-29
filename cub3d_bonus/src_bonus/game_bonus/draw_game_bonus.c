/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:56:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/29 11:44:35 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	cast_ray_dda(t_img *img, double ray_angle, int column);

void	draw_wall(t_img *img, int x, double wall_size, double angle)
{
	int	y;
	int	color_c;
	int	color_f;

	color_f = (img->game->f_text_rgb[0] << 16) | (img->game->f_text_rgb[1] << 8) | img->game->f_text_rgb[2];
	color_c = (img->game->c_text_rgb[0] << 16) | (img->game->c_text_rgb[1] << 8) | img->game->c_text_rgb[2];
	y = 0;
	img->wall_start = (SCREEN_HEIGHT / 2) - (wall_size / 2);
	img->wall_end = (SCREEN_HEIGHT / 2) + (wall_size / 2);
	while (y < SCREEN_HEIGHT)
	{
		if (y < img->wall_start)
			my_put_pixel(img, x, y, color_c);
		else if (y < img->wall_end)
			draw_wall_text(img, x, y, angle);
		else
			my_put_pixel(img, x, y, color_f);
		y++;
	}
}

/**
 * @brief Balaye l'écran par colonnes et lance le raycasting DDA.
 * 
 * Calcule l'incrément d'angle en fonction du FOV et de SCREEN_WIDTH
 * et itère sur chaque colonne pour lancer cast_ray_dda.
 * 
 * @param img
 */
static void	calc_and_draw_angle(t_img *img)
{
	double	angle_step;
	double	angle;
	int		i;

	i = 0;
	angle_step = FOV / SCREEN_WIDTH;
	while (i < SCREEN_WIDTH)
	{
		angle = img->player->direction_vue - (FOV / 2) + (i * angle_step);
		cast_ray_dda(img, angle, i);
		i++;
	}
}

/**
 * @brief Redessine la scène (rayons / murs) et affiche l'image.
 * 
 * Lance le calcul et le rendu des rayons, puis pousse l'image résultante vers
 * la fenêtre via mlx_put_image_to_window.
 * 
 * @param img
 */
void	put_cub3d_to_wnd(t_img *img)
{
	calc_and_draw_angle(img);
	mlx_put_image_to_window(img->game->mlx, img->game->win, img->img, 0, 0);
}
