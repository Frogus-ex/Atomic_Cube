/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:38:02 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/15 17:43:46 by aautret          ###   ########.fr       */
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
	int	last_player_y;
	int	last_player_x;

	last_player_x = img->player->origin_x;
	last_player_y = img->player->origin_y;
	if (keycode == ESC)
		cleanup(img->game);
	if (keycode == UP || keycode == W)
		img->player->origin_y -= 5;
	if (keycode == DOWN || keycode == S)
		img->player->origin_y += 5;
	if (keycode == RIGHT || keycode == D)
		img->player->origin_x += 5;
	if (keycode == LEFT || keycode == A)
		img->player->origin_x -= 5;
	draw_initial_dot(img);
	return (0);
}

// void	player_moves(t_img *img, int new_y, int new_x)
// {
// 	int	last_x;
// 	int	last_y;

// 	last_x = img->player->x;
// 	last_y = img->player->y;
// 	if (new_y < 0 || new_y >= img->height || new_x < 0 || new_x >= img->width)
// 		ft_error(img->game, "depassement de map");
// 	else if (img->map->map[new_y][new_x] == '0')
// 	{
// 		img->map->map[last_y][last_x] = '0';
// 		img->player->x = new_x;
// 		img->player->y = new_y;
// 		img->map->map[new_y][new_x] = 'N';
// 		draw_map(img);
// 	}
// }
