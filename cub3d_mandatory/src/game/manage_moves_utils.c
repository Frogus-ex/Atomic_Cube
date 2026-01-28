/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:54:06 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/28 13:35:46 by tlorette         ###   ########.fr       */
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
