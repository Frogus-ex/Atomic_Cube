/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:18:39 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/09 12:52:01 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

static int	parsing_check_all(t_game *game, char **av, t_map *map)
{
	if (!check_arg_param(av))
		return (1);
	if (parsing(game, av[1]))
		return (1);
	read_from_map(game, map, av[1]);
	if (flood_fill(map))
		return (1);
	game->av = av[1];
	return (0);
}

static int	init_img_and_player(t_game *game, t_texture *texture)
{
	t_img		*img;
	t_player	*player;
	t_minimap	*minimap;

	player = NULL;
	minimap = NULL;
	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (0);
	ft_bzero(img, sizeof(t_img));
	img->texture = texture;
	game->img = img;
	player_init(&player, game);
	if (!player)
		return (0);
	minimap_init(&minimap);
	if (!minimap)
		return (0);
	game->minimap = minimap;
	minimap->player_pos_x = 0;
	minimap->player_pos_y = 0;
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
	game->animate = NULL;
	map->s_animate = NULL;
	text_init(&texture);
	if (!texture)
		return (free_all(game), NULL);
	game->textures = texture;
	if (!init_img_and_player(game, texture))
		return (free_all(game), NULL);
	return (game);
}

static void	load_all_sprites(t_game *game)
{
	int	i;

	if (!game->map || game->map->sprite_count <= 0)
		return ;
	i = 0;
	while (i < game->map->sprite_count)
	{
		game->map->sprites[i]->x = game->map->sprites[i]->x * TILE_SIZE
			+ TILE_SIZE / 2;
		game->map->sprites[i]->y = game->map->sprites[i]->y * TILE_SIZE
			+ TILE_SIZE / 2;
		if (!load_sprite(game, game->map->sprites[i]))
			ft_error(NULL, "failed to load animated sprite");
		i++;
	}
	if (game->map->s_animate)
		game->animate = game->map->s_animate;
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (ft_error(NULL, "wrong number of args"), 1);
	game = init_all();
	if (!game)
		return (ft_error(NULL, "Failed to initialize game"), 1);
	if (parsing_check_all(game, av, game->map))
		return (free_all(game), 1);
	game->img->game = game;
	game->img->map = game->map;
	game->img->player = game->player;
	game->img->player->origin_x = game->map->player_x * TILE_SIZE + TILE_SIZE
		/ 2;
	game->img->player->origin_y = game->map->player_y * TILE_SIZE + TILE_SIZE
		/ 2;
	game->minimap->player_pos_x = game->map->player_x * MINIMAP_WIDTH
		+ MINIMAP_WIDTH / 2;
	game->minimap->player_pos_y = game->map->player_y * MINIMAP_HEIGHT
		+ MINIMAP_HEIGHT / 2;
	if (!check_colors_param(game))
		return (ft_error(game, "colors param are not in RGB format"), 0);
	if (!init_mlx(game, game->map, game->img))
		return (0);
	load_all_sprites(game);
	render_frame(game->img);
	mlx_loop(game->mlx);
	return (free_all(game), 0);
}
