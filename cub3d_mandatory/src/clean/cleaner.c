/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:08:43 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/29 13:42:39 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_map_array(t_map *map)
{
	int	i;

	if (!map || !map->map)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	map->map = NULL;
}

static void	free_struct(t_game *game)
{
	if (!game)
		return ;
	if (game->no_text)
		free(game->no_text);
	if (game->so_text)
		free(game->so_text);
	if (game->we_text)
		free(game->we_text);
	if (game->ea_text)
		free(game->ea_text);
	if (game->f_text)
		free(game->f_text);
	if (game->c_text)
		free(game->c_text);
	if (game->nbr_text)
		free(game->nbr_text);
	if (game->player)
		free(game->player);
	if (game->c_rgb)
		free(game->c_rgb);
	if (game->f_rgb)
		free(game->f_rgb);
}

void	free_all(t_game *game)
{
	if (!game)
		return ;
	free_struct(game);
	if (game->map)
		free_map(game->map);
	if (game->textures)
	{
		if (game->textures->tex_no_img && game->mlx)
			mlx_destroy_image(game->mlx, game->textures->tex_no_img);
		if (game->textures->tex_so_img && game->mlx)
			mlx_destroy_image(game->mlx, game->textures->tex_so_img);
		if (game->textures->tex_ea_img && game->mlx)
			mlx_destroy_image(game->mlx, game->textures->tex_ea_img);
		if (game->textures->tex_we_img && game->mlx)
			mlx_destroy_image(game->mlx, game->textures->tex_we_img);
		free(game->textures);
	}
	if (game->img)
	{
		if (game->img->img && game->mlx)
			mlx_destroy_image(game->mlx, game->img->img);
		free(game->img);
	}
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
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
