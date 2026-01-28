/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:56:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/28 11:21:16 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_colision(t_img *img, double px, double py)
{
	int	tx;
	int	ty;

	if (!img || !img->map || !img->map->map || px < 0 || py < 0)
		return (0);
	tx = (int)floor(px / TILE_SIZE);
	ty = (int)floor(py / TILE_SIZE);
	if (ty < 0 || ty >= img->map->height || tx < 0 || tx >= img->map->width)
		return (0);
	if (!img->map->map[ty] || !img->map->map[ty][tx])
		return (0);
	if (img->map->map[ty][tx] == '1')
		return (0);
	return (1);
}

/**
 * @brief Trace un rayon sur la mini-map pour un angle absolu.
 * @param img image cible
 * @param angle angle du rayon en radians
 */
static void	draw_angle_new(t_img *img, double angle, int collumn)
{
	double	step_x;
	double	step_y;
	double	current_x;
	double	current_y;
	int		i;

	if (!img || !img->player)
		return ;
	img->player->view_angle = img->player->direction_vue + (-M_PI / 8);
	img->distance_x = img->player->origin_x + 110 * cos(angle);
	img->distance_y = img->player->origin_y + 110 * sin(angle);
	step_x = (img->distance_x - img->player->origin_x) / 110;
	step_y = (img->distance_y - img->player->origin_y) / 110;
	i = 0;
	while (i < find_biggest(img))
	{
		current_x = img->player->origin_x + step_x * i;
		current_y = img->player->origin_y + step_y * i;
		if (!check_colision(img, current_x, current_y))
		{
			get_wall_hit(img->texture, current_x, current_y);
			get_distance(img, current_x, current_y, angle);
			draw_wall(img, collumn, img->wall_size, angle);
			break ;
		}
		// my_put_pixel(img, current_x, current_y, 0xFFFF00);
		i++;
	}
}

/**
 * @brief Dessine les rayons depuis la position courante du joueur
 *
 * Calcule et affiche le faisceau de rayons autour de la direction vue.
 * @param img image cible
 */
static void	calc_and_draw_angle(t_img *img)
{
	double	angle_step;
	double	angle;
	int		i;

	i = 0;
	angle_step = (M_PI / 4) / img->width;
	while (i < img->width)
	{
		angle = img->player->direction_vue - (M_PI / 8) + (i * angle_step);
		draw_angle_new(img, angle, i);
		i++;
	}
}



/**
 * @brief Redessine la mini-carte (tuiles, joueur, rayons) et affiche la frame.
 * @param map representation grille
 * @param img image cible
 */
void	put_cub3d_to_wnd(t_img *img)
{
	calc_and_draw_angle(img);
	mlx_put_image_to_window(img->game->mlx, img->game->win, img->img, 0, 0);
}
