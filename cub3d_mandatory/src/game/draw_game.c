/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:56:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/29 13:41:56 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void		cast_ray_dda(t_img *img, double ray_angle, int column);

void	draw_wall(t_game *game, int x, double wall_size, double angle)
{
	int	y;
	int	color_c;
	int	color_f;

	color_f = (game->f_rgb[0] << 16) | (game->f_rgb[1] << 8) | game->f_rgb[2];
	color_c = (game->c_rgb[0] << 16) | (game->c_rgb[1] << 8) | game->c_rgb[2];
	y = 0;
	game->img->wall_start = (SCREEN_HEIGHT / 2) - (wall_size / 2);
	game->img->wall_end = (SCREEN_HEIGHT / 2) + (wall_size / 2);
	while (y < SCREEN_HEIGHT)
	{
		if (y < game->img->wall_start)
			my_put_pixel(game->img, x, y, color_c);
		else if (y < game->img->wall_end)
			draw_wall_text(game->img, x, y, angle);
		else
			my_put_pixel(game->img, x, y, color_f);
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
