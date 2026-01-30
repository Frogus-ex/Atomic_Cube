/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:38:02 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/30 13:46:34 by tlorette         ###   ########.fr       */
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
	put_cub3d_to_wnd(img);
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

static void	simple_mooves(t_game *game, t_img *img)
{
	if (game->player->w_pressed)
		moving_pix_by_pix(img, calc_dx(img, W), calc_dy(img, W));
	if (game->player->s_pressed)
		moving_pix_by_pix(img, calc_dx(img, S), calc_dy(img, S));
	if (game->player->a_pressed)
		moving_pix_by_pix(img, calc_dx(img, A), calc_dy(img, A));
	if (game->player->d_pressed)
		moving_pix_by_pix(img, calc_dx(img, D), calc_dy(img, D));
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
 * @param param Pointeur vers t_img casté en void*
 * @return int Toujours 0.
 */
int	player_input(t_game *game)
{
	int		need_redraw;
	t_img	*img;

	if (!game || !game->img || !game->player)
		return (0);
	img = game->img;
	need_redraw = 0;
	simple_mooves(game, img);
	if (game->player->right_pressed)
	{
		game->player->direction_vue += 0.05;
		if (game->player->direction_vue >= 2 * M_PI)
			game->player->direction_vue -= 2 * M_PI;
		need_redraw = 1;
	}
	if (game->player->left_pressed)
	{
		game->player->direction_vue -= 0.05;
		if (game->player->direction_vue < 0)
			game->player->direction_vue += 2 * M_PI;
		need_redraw = 1;
	}
	if (need_redraw)
		put_cub3d_to_wnd(img);
	return (0);
}
