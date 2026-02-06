/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:39:38 by autret            #+#    #+#             */
/*   Updated: 2026/02/06 11:35:01 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

void	simple_mooves(t_game *game, t_img *img)
{
	if (!game || !game->player || !img)
		return ;
	if (game->player->w_pressed)
		moving_pix_by_pix(img, calc_dx(img, W), calc_dy(img, W));
	if (game->player->s_pressed)
		moving_pix_by_pix(img, calc_dx(img, S), calc_dy(img, S));
	if (game->player->a_pressed)
		moving_pix_by_pix(img, calc_dx(img, A), calc_dy(img, A));
	if (game->player->d_pressed)
		moving_pix_by_pix(img, calc_dx(img, D), calc_dy(img, D));
	if (game->player->space_pressed && !game->player->space_was_pressed)
	{
		open_door(game);
		game->player->space_was_pressed = 1;
	}
	else if (!game->player->space_pressed)
		game->player->space_was_pressed = 0;
}

static void	handle_rotation(t_game *game)
{
	int		current_x;
	int		delta_x;
	float	rotation_speed;

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
}

int	game_loop(t_game *game)
{
	static int	last_time;
	int			current_time;
	int			delta_ms;

	if (!game || !game->player || !game->img)
		return (0);
	current_time = clock() * 1000 / CLOCKS_PER_SEC;
	delta_ms = current_time - last_time;
	if (last_time == 0)
		delta_ms = 16;
	last_time = current_time;
	handle_rotation(game);
	simple_mooves(game, game->img);
	update_all_sprites(game, delta_ms);
	render_frame(game->img);
	return (0);
}
