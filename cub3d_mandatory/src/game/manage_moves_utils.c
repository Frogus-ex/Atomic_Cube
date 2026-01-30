/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_moves_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:54:06 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/30 10:10:41 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	key_press(int keycode, t_game *game)
{
	if (!game || !game->player)
		return (0);
	if (keycode == ESC)
		return (cleanup(game), 0);
	if (keycode == W)
		game->player->w_pressed = 1;
	if (keycode == S)
		game->player->s_pressed = 1;
	if (keycode == A)
		game->player->a_pressed = 1;
	if (keycode == D)
		game->player->d_pressed = 1;
	if (keycode == LEFT)
		game->player->left_pressed = 1;
	if (keycode == RIGHT)
		game->player->right_pressed = 1;
	return (0);
}

int	key_released(int keycode, t_game *game)
{
	if (!game || !game->player)
		return (0);
	if (keycode == ESC)
		return (cleanup(game), 0);
	if (keycode == W)
		game->player->w_pressed = 0;
	if (keycode == S)
		game->player->s_pressed = 0;
	if (keycode == A)
		game->player->a_pressed = 0;
	if (keycode == D)
		game->player->d_pressed = 0;
	if (keycode == LEFT)
		game->player->left_pressed = 0;
	if (keycode == RIGHT)
		game->player->right_pressed = 0;
	return (0);
}

int	collision_checker(t_img *img)
{
	if (img->map->map[(int)floor((img->ny + 10)
				/ TILE_SIZE)][(int)floor((img->nx + 10) / TILE_SIZE)] != '1'
		&& img->map->map[(int)floor((img->ny - 10)
			/ TILE_SIZE)][(int)floor((img->nx - 10) / TILE_SIZE)] != '1'
		&& img->map->map[(int)floor((img->ny + 10)
			/ TILE_SIZE)][(int)floor((img->nx - 10) / TILE_SIZE)] != '1'
		&& img->map->map[(int)floor((img->ny - 10)
			/ TILE_SIZE)][(int)floor((img->nx + 10) / TILE_SIZE)] != '1')
		return (1);
	return (0);
}
