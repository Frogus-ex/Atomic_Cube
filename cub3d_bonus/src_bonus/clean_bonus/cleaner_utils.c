/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: autret <autret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:44:42 by aautret           #+#    #+#             */
/*   Updated: 2026/02/05 16:20:29 by autret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

void	free_texture_in_game(t_game *game)
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

/**
 * @brief Libère un sprite et ses frames
 */
static void	free_single_sprite(t_game *game, t_animate *sprite)
{
	int	i;

	if (!sprite)
		return ;
	i = 0;
	while (i < sprite->frame_count)
	{
		if (sprite->frame[i] && game && game->mlx)
			mlx_destroy_image(game->mlx, sprite->frame[i]);
		i++;
	}
	free(sprite);
}

/**
 * @brief Libère tous les sprites de la map
 */
void	free_all_sprites(t_game *game, t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->sprites && map->sprite_count > 0)
	{
		i = 0;
		while (i < map->sprite_count)
		{
			free_single_sprite(game, map->sprites[i]);
			i++;
		}
		free(map->sprites);
		map->sprites = NULL;
	}
	map->sprite_count = 0;
	map->s_animate = NULL;
}

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

void	free_struct(t_game *game)
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
	game->animate = NULL;
}
