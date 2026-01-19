/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:38:02 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/19 11:07:31 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/**
 * @brief Libère la mémoire et ferme proprement le programme
 *
 * @param game
 * @return int
 */
int	cleanup(t_game *game)
{
	if (!game)
		exit(EXIT_FAILURE);
	if (game->map)
		free_all(game);
	if (game->img && game->mlx && game->img->img)
		mlx_destroy_image(game->mlx, game->img->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
	exit(EXIT_FAILURE);
}

/**
 * @brief Gère la fermeture de la fenêtre via la croix
 *
 * @param game
 * @return int
 */
int	cross_close(t_game *game)
{
	cleanup(game);
	return (0);
}

/**
 * @brief Gère les entrées clavier du joueur et met à jour sa position
 *
 * @param keycode
 * @param img
 * @return int
 */
int	player_input(int keycode, t_img *img)
{
	if (keycode == ESC)
		cleanup(img->game);
	if (keycode == W)
		player_moves(img, img->map->player_y - 1, img->map->player_x);
	if (keycode == S)
		player_moves(img, img->map->player_y + 1, img->map->player_x);
	if (keycode == D)
		player_moves(img, img->map->player_y, img->map->player_x + 1);
	if (keycode == A)
		player_moves(img, img->map->player_y, img->map->player_x - 1);
	if (keycode == LEFT)
		player_moves(img, img->player->view_angle);
	if (keycode == RIGHT)
		player_moves(img, img->map->player_y, img->map->player_x - 1);
	return (0);
}

void	player_moves(t_img *img, int new_y, int new_x)
{
	int	last_x;
	int	last_y;

	last_x = img->map->player_x;
	last_y = img->map->player_y;
	if (new_y < 0 || new_y >= img->height || new_x < 0 || new_x >= img->width)
		ft_error(img->game, "depassement de map");
	else if (img->map->map[new_y][new_x] == '0')
	{
		img->map->map[last_y][last_x] = '0';
		img->map->player_x = new_x;
		img->map->player_y = new_y;
		img->map->map[new_y][new_x] = 'N';
		make_pixel(img->map, img);
	}
}
