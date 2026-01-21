/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:18:39 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/21 17:52:59 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int ac, char **av)
{
	t_game		*game;
	t_map		*map;
	t_img		*img;
	t_player	*player;

	if (ac != 2)
		return (ft_error(NULL, "wrong number of args"), 1);
	game_init(&game);
	if (!game)
		return (1);
	map_init(&map);
	if (!map)
		return (free(game), 1);
	game->map = map;
	img_init(&img);
	if (!img)
		return (free_all(game), 1);
	game->img = img;
	player_init(&player, game);
	if (!player)
		return (free_all(game), 1);
	if (parsing(game, av[1]))
		return (free_all(game), 1);
	read_from_map(game, map, av[1]);
	if (flood_fill(game, map))
		return (free_all(game), 1);
	img->game = game;
	img->map = map;
	img->player = player;
	// initialize player origin in pixels from map start position
	img->player->origin_x = img->map->player_x * TILE_SIZE + TILE_SIZE / 2;
	img->player->origin_y = img->map->player_y * TILE_SIZE + TILE_SIZE / 2;
	// initialize player origin in pixels from map start position
	img->player->origin_x = img->map->player_x * TILE_SIZE + TILE_SIZE / 2;
	img->player->origin_y = img->map->player_y * TILE_SIZE + TILE_SIZE / 2;
	init_mlx(game, map, img);
	draw_minimap(map, img);
	mlx_loop(game->mlx);
	return (free_all(game), 0);
}
