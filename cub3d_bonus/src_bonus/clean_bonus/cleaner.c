/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:08:43 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/06 11:18:43 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

static void	free_game_resources(t_game *game)
{
	if (game->map)
	{
		free_all_sprites(game, game->map);
		free_map(game->map);
	}
	if (game->textures)
		free_texture_in_game(game);
	if (game->img)
	{
		if (game->img->img && game->mlx)
			mlx_destroy_image(game->mlx, game->img->img);
		free(game->img);
	}
}

static void	free_mlx_resources(t_game *game)
{
	if (game->minimap)
		free(game->minimap);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	free_all(t_game *game)
{
	if (!game)
		return ;
	free_struct(game);
	free_game_resources(game);
	free_mlx_resources(game);
	if (game->fd >= 0)
		close(game->fd);
	free(game);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_map_array(map);
	free_tmp_map(map);
	free(map);
}

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
	exit(EXIT_FAILURE);
}
