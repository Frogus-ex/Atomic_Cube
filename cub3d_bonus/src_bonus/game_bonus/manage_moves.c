/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: autret <autret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:38:02 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/05 16:46:33 by autret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

/**
 * @brief Déplace le joueur pixel par pixel en testant la collision.
 *
 * Calcule la case cible à partir de la position candidate (origin_x + dx,
 * origin_y + dy). Si la case cible est hors-map ou est un mur ('1'), le
 * déplacement est annulé. Sinon met à jour origin_x/origin_y (en int)
 * puis redessine la mini-map.
 *
 * @param img  Pointeur vers la structure image
	/ état (doit contenir map et player).
 * @param dx   Déplacement en pixels sur l'axe X
 * @param dy   Déplacement en pixels sur l'axe Y
 */
void	moving_pix_by_pix(t_img *img, double dx, double dy)
{
	if (!img || !img->player || !img->map)
		return ;
	img->nx = (double)img->player->origin_x + dx;
	img->ny = (double)img->player->origin_y + dy;
	img->tx = (int)floor(img->nx / TILE_SIZE);
	img->ty = (int)floor(img->ny / TILE_SIZE);
	if (img->tx < 0 || img->ty < 0 || img->tx >= img->map->width
		|| img->ty >= img->map->height)
		return ;
	if (img->map->map[img->ty][img->tx] != '1' && collision_checker(img))
	{
		img->player->origin_x = (int)round(img->nx);
		img->player->origin_y = (int)round(img->ny);
	}
}

double	calc_dx(t_img *img, int keycode)
{
	double	dx;
	double	speed;

	dx = 0.0;
	speed = 2.5;
	if (!img || !img->player)
		return (dx);
	speed = 7.5;
	if (keycode == W)
		dx = cos(img->player->direction_vue) * speed;
	else if (keycode == S)
		dx = (-1) * (cos(img->player->direction_vue) * speed);
	else if (keycode == D)
		dx = cos(img->player->direction_vue + M_PI_2) * speed;
	else if (keycode == A)
		dx = cos(img->player->direction_vue - M_PI_2) * speed;
	return (dx);
}

double	calc_dy(t_img *img, int keycode)
{
	double	dy;
	double	speed;

	dy = 0.0;
	speed = 2.5;
	if (!img || !img->player)
		return (dy);
	speed = 7.5;
	if (keycode == W)
		dy = sin(img->player->direction_vue) * speed;
	else if (keycode == S)
		dy = (-1) * (sin(img->player->direction_vue) * speed);
	else if (keycode == D)
		dy = sin(img->player->direction_vue + M_PI_2) * speed;
	else if (keycode == A)
		dy = sin(img->player->direction_vue - M_PI_2) * speed;
	return (dy);
}

void	update_all_sprites(t_game *game, int delta_ms)
{
	int	i;

	if (!game->map || game->map->sprite_count <= 0)
		return ;
	i = 0;
	while (i < game->map->sprite_count)
	{
		update_sprite_animation(game->map->sprites[i], delta_ms);
		i++;
	}
}
