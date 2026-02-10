/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:18:39 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/10 13:25:12 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	parsing_check_all(t_game *game, char **av, t_map *map)
{
	if (!check_arg_param(av))
		return (1);
	if (parsing(game, av[1]))
		return (1);
	read_from_map(game, map, av[1]);
	if (flood_fill(map))
		return (1);
	return (0);
}

static int	init_img_and_player(t_game *game, t_texture *texture)
{
	t_img		*img;
	t_player	*player;

	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (0);
	ft_bzero(img, sizeof(t_img));
	img->texture = texture;
	game->img = img;
	player_init(&player, game);
	if (!player)
		return (0);
	return (1);
}

t_game	*init_all(void)
{
	t_game		*game;
	t_map		*map;
	t_texture	*texture;

	game_init(&game);
	if (!game)
		return (NULL);
	map_init(&map);
	if (!map)
		return (free_all(game), NULL);
	game->map = map;
	text_init(&texture);
	if (!texture)
		return (free_all(game), NULL);
	game->textures = texture;
	if (!init_img_and_player(game, texture))
		return (free_all(game), NULL);
	return (game);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (ft_error(NULL, "wrong number of args"), 1);
	game = init_all();
	if (!game)
		return (ft_error(NULL, "Failed to initialize game"), 1);
	if (parsing_check_all(game, av, game->map) == 1)
		return (free_all(game), 1);
	game->img->game = game;
	game->img->map = game->map;
	game->img->player = game->player;
	game->img->player->origin_x = game->map->player_x * TILE_SIZE + TILE_SIZE
		/ 2;
	game->img->player->origin_y = game->map->player_y * TILE_SIZE + TILE_SIZE
		/ 2;
	if (!check_colors_param(game))
		return (ft_error(game, "colors param are not in RGB format"), 0);
	if (!init_mlx(game, game->map, game->img))
		return (0);
	put_cub3d_to_wnd(game->img);
	mlx_loop(game->mlx);
	return (free_all(game), 0);
}
