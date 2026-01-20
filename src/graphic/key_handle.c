/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:38:02 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/20 16:18:00 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
static void	moving_pix_by_pix(t_img *img, double dx, double dy)
{
	double	nx;
	double	ny;
	int		tx;
	int		ty;

	if (!img || !img->player || !img->map)
		return ;
	nx = (double)img->player->origin_x + dx;
	ny = (double)img->player->origin_y + dy;
	tx = (int)floor(nx / TILE_SIZE);
	ty = (int)floor(ny / TILE_SIZE);
	if (tx < 0 || ty < 0 || tx >= img->map->width || ty >= img->map->height)
		return ;
	if (img->map->map[ty][tx] != '1')
	{
		img->player->origin_x = (int)round(nx);
		img->player->origin_y = (int)round(ny);
	}
	draw_minimap(img->map, img);
}

static double	calc_dx(t_img *img, int keycode)
{
	double	dx;
	double	speed;

	dx = 0.0;
	speed = 2.5;
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

static double	calc_dy(t_img *img, int keycode)
{
	double	dy;
	double	speed;

	dy = 0.0;
	speed = 2.5;
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

/**
 * @brief Gère les entrées clavier et déclenche les actions correspondantes
 *
 * Touches gérées :
 *  - W/S : avancer / reculer (avec dx/dy calculés depuis direction_vue)
 *  - A/D :gauche/droite
 *  - LEFT/RIGHT : rotation de la vue (modifie direction_vue et redessine)
 *  - ESC : quitte via cleanup()
 *
 * @param keycode Code de la touche reçue.
 * @param img
 * @return int Toujours 0.
 */
int	player_input(int keycode, t_img *img)
{
	if (keycode == ESC)
		cleanup(img->game);
	if (keycode == W)
		moving_pix_by_pix(img, calc_dx(img, keycode), calc_dy(img, keycode));
	if (keycode == S)
		moving_pix_by_pix(img, calc_dx(img, keycode), calc_dy(img, keycode));
	if (keycode == A)
		moving_pix_by_pix(img, calc_dx(img, keycode), calc_dy(img, keycode));
	if (keycode == D)
		moving_pix_by_pix(img, calc_dx(img, keycode), calc_dy(img, keycode));
	if (keycode == RIGHT)
		img->player->direction_vue += 0.1;
	if (keycode == LEFT)
		img->player->direction_vue -= 0.1;
	if (keycode == LEFT || keycode == RIGHT)
		draw_minimap(img->map, img);
	return (0);
}
