/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:38:02 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/06 11:40:48 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

/**
 * @brief Déplace le joueur pixel par pixel en testant la collision.
 *
 * Applique les déplacements séparément en X puis en Y pour permettre
 * le glissement le long des murs (sliding collision).
 *
 * @param img  Pointeur vers la structure image (doit contenir map et player).
 * @param dx   Déplacement en pixels sur l'axe X
 * @param dy   Déplacement en pixels sur l'axe Y
 */
void	moving_pix_by_pix(t_img *img, double dx, double dy)
{
	if (!img || !img->player || !img->map)
		return ;
	img->nx = (double)img->player->origin_x + dx;
	img->ny = (double)img->player->origin_y;
	img->tx = (int)floor(img->nx / TILE_SIZE);
	img->ty = (int)floor(img->ny / TILE_SIZE);
	if (img->tx >= 0 && img->ty >= 0 && img->tx < img->map->width
		&& img->ty < img->map->height)
	{
		if (img->map->map[img->ty][img->tx] != '1' && collision_checker(img))
			img->player->origin_x = (int)round(img->nx);
	}
	img->nx = (double)img->player->origin_x;
	img->ny = (double)img->player->origin_y + dy;
	img->tx = (int)floor(img->nx / TILE_SIZE);
	img->ty = (int)floor(img->ny / TILE_SIZE);
	if (img->tx >= 0 && img->ty >= 0 && img->tx < img->map->width
		&& img->ty < img->map->height)
	{
		if (img->map->map[img->ty][img->tx] != '1' && collision_checker(img))
			img->player->origin_y = (int)round(img->ny);
	}
}

double	calc_dx(t_img *img, int keycode)
{
	double	dx;
	double	speed;

	dx = 0.0;
	speed = 5;
	if (!img || !img->player)
		return (dx);
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
	speed = 5;
	if (!img || !img->player)
		return (dy);
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

int	handle_player_input(t_game *game)
{
	int		current_x;
	int		delta_x;
	float	rotation_speed;

	if (!game || !game->player || !game->img)
		return (0);
	current_x = 0;
	mlx_mouse_get_pos(game->mlx, game->win, &current_x, &game->player->mouse_y);
	delta_x = current_x - game->player->mouse_x;
	game->player->mouse_x = current_x;
	rotation_speed = 0.005f;
	if (delta_x != 0)
		game->player->direction_vue += delta_x * rotation_speed;
	if (game->player->left_pressed)
		game->player->direction_vue -= 0.05;
	if (game->player->right_pressed)
		game->player->direction_vue += 0.05;
	simple_mooves(game, game->img);
	render_frame(game->img);
	return (0);
}
