/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:44:58 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/04 17:01:50 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

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

static void	find_nearest_door(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map->width || y < 0 || y >= game->map->height)
		return ;
	if (game->map->tmp_map[y][x] == '1' || game->map->tmp_map[y][x] == 'V')
		return ;
	if (game->map->map[y][x] == 'D')
	{
		game->map->door_pos_x = x;
		game->map->door_pos_y = y;
		return ;
	}
	game->map->tmp_map[y][x] = 'V';
	find_nearest_door(game, x, y + 1);
	find_nearest_door(game, x, y - 1);
	find_nearest_door(game, x + 1, y);
	find_nearest_door(game, x - 1, y);
}

void	open_door(t_game *game)
{
	re_read_from_map(game, game->map, game->av);
	find_nearest_door(game, game->map->player_x, game->map->player_y);
	if (game->door_open == 0)
	{
		game->map->map[game->map->door_pos_y][game->map->door_pos_x] = '0';
		game->door_open = 1;
	}
	else if (game->door_open == 1)
	{
		game->map->map[game->map->door_pos_y][game->map->door_pos_x] = 'D';
		game->door_open = 0;
	}
}
