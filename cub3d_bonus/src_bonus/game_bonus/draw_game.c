/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:56:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/06 11:19:04 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

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

	if (!img || !img->player)
		return ;
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
}

/**
 * @brief Dessine le rendu 3D + la minimap puis affiche tout.
 *
 * Rendu complet : raycasting 3D + puis les sprites animés + 
 * la minimap par-dessus + affiche l'image finale.
 *
 * @param img Structure contenant l'image et les données du jeu
 */
void	render_frame(t_img *img)
{
	int	i;

	put_cub3d_to_wnd(img);
	if (img->map && img->map->sprite_count > 0)
	{
		i = 0;
		while (i < img->map->sprite_count)
		{
			draw_sprite_3d(img->game, img, img->map->sprites[i]);
			i++;
		}
	}
	draw_minimap(img->map, img);
	mlx_put_image_to_window(img->game->mlx, img->game->win, img->img, 0, 0);
}
