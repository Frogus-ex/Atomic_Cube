/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:38:02 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/20 15:49:05 by aautret          ###   ########.fr       */
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
	else if (keycode == A)
		dx = cos(img->player->direction_vue + M_PI_2) * speed;
	else if (keycode == D)
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
	else if (keycode == A)
		dy = cos(img->player->direction_vue - M_PI_2) * speed;
	else if (keycode == D)
		dy = cos(img->player->direction_vue - M_PI_2) * speed;
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

/**
 * @brief Déplace le joueur d'une case à une autre (déplacement par tile/cases)
 *
 * Utilisé actuellement pour le déplacement tile-by-tile. Vérifie que la case
 * cible (new_y, new_x) est dans la map et libre ('0'), met à jour la map
 * (ancienne case -> '0', nouvelle -> 'N'), met l'origine du joueur au centre
 * de la nouvelle case et redessine la mini-map.
 *
 * @param img
 * @param new_y Indice ligne de la destination (tile)
 * @param new_x Indice colonne de la destination (tile)
 */
void	player_moves(t_img *img, int new_y, int new_x)
{
	int	last_x;
	int	last_y;

	last_x = img->map->player_x;
	last_y = img->map->player_y;
	if (new_y < 0 || new_y >= img->map->height || new_x < 0
		|| new_x >= img->map->width)
		ft_error(img->game, "depassement de map");
	else if (img->map->map[new_y][new_x] == '0')
	{
		img->map->map[last_y][last_x] = '0';
		img->map->player_x = new_x;
		img->map->player_y = new_y;
		img->map->map[new_y][new_x] = 'N';
		img->player->origin_x = img->map->player_x * TILE_SIZE + TILE_SIZE / 2;
		img->player->origin_y = img->map->player_y * TILE_SIZE + TILE_SIZE / 2;
		draw_minimap(img->map, img);
	}
}
