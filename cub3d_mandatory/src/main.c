/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:18:39 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/30 10:38:28 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	parsing_check_all(t_game *game, char **av, t_map *map)
{
	if (parsing(game, av[1]))
		return (free_all(game), 1);
	read_from_map(game, map, av[1]);
	if (flood_fill(map))
		return (free_all(game), 1);
	return (0);
}

t_game	*init_all(void)
{
	t_game		*game;
	t_map		*map;
	t_img		*img;
	t_texture	*texture;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	ft_bzero(game, sizeof(t_game));
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (free(game), NULL);
	ft_bzero(map, sizeof(t_map));
	game->map = map;
	texture = (t_texture *)malloc(sizeof(t_texture));
	if (!texture)
		return (free_all(game), NULL);
	ft_bzero(texture, sizeof(t_texture));
	game->textures = texture;
	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (free_all(game), NULL);
	ft_bzero(img, sizeof(t_img));
	game->img = img;
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
	if (!parsing_check_all(game, av, game->map))
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
