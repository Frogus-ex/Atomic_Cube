/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:44:58 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/06 13:26:09 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"
#include <limits.h>

static void	re_read_from_map(t_game *game, t_map *map, char *av)
{
	char	*stash;
	char	*line;
	int		detect;

	stash = NULL;
	game->fd = open(av, O_RDONLY);
	if (game->fd < 0)
		return (ft_error(NULL, "file doesnt exist"));
	line = get_next_line(game->fd, &stash);
	if (!alloc_tmp_map(map))
		return (free(line), free(stash), close(game->fd), ft_error(game,
				"tmp_map allocation failed"));
	map->y = 0;
	while (line)
	{
		detect = detector_start_map(line);
		if (detect == 1)
			map_copy(map, line);
		free(line);
		line = get_next_line(game->fd, &stash);
	}
	free(stash);
	close(game->fd);
}

static void	reset_tmp_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->tmp_map[y][x] == 'V')
				game->map->tmp_map[y][x] = '0';
			x++;
		}
		y++;
	}
}

static void	find_nearest_door(t_game *game, int x, int y, int distance)
{
	if (x < 0 || x >= game->map->width || y < 0 || y >= game->map->height)
		return ;
	if (game->map->tmp_map[y][x] == '1' || game->map->tmp_map[y][x] == 'V')
		return ;
	if (game->map->map[y][x] == 'D')
	{
		if (game->map->door_pos_x == -1 || distance < game->map->door_distance)
		{
			game->map->door_pos_x = x;
			game->map->door_pos_y = y;
			game->map->door_distance = distance;
		}
		return ;
	}
	game->map->tmp_map[y][x] = 'V';
	find_nearest_door(game, x + 1, y, distance + 1);
	find_nearest_door(game, x - 1, y, distance + 1);
	find_nearest_door(game, x, y + 1, distance + 1);
	find_nearest_door(game, x, y - 1, distance + 1);
}

static void	reset_open_door_varaible(t_game *game)
{
	game->player_tile_x = (int)floor((double)game->img->player->origin_x
			/ TILE_SIZE);
	game->player_tile_y = (int)floor((double)game->img->player->origin_y
			/ TILE_SIZE);
	game->map->door_pos_x = -1;
	game->map->door_pos_y = -1;
	game->map->door_distance = INT_MAX;
}

void	open_door(t_game *game)
{
	reset_open_door_varaible(game);
	re_read_from_map(game, game->map, game->av);
	find_nearest_door(game, game->player_tile_x, game->player_tile_y, 0);
	reset_tmp_map(game);
	if (game->map->door_pos_x == -1 || game->map->door_pos_y == -1)
		return ;
	if (game->door_open == 0)
	{
		game->map->map[game->map->door_pos_y][game->map->door_pos_x] = '0';
		game->door_open = 1;
	}
	else if (game->door_open == 1
		&& game->map->map[game->map->door_pos_y][game->map->door_pos_x]
		!= game->map->map[game->player_tile_y][game->player_tile_x])
	{
		game->map->map[game->map->door_pos_y][game->map->door_pos_x] = 'D';
		game->door_open = 0;
	}
	else
		game->map->map[game->map->door_pos_y][game->map->door_pos_x] = '0';
}
