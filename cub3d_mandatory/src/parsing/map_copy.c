/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:38:28 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/29 16:24:07 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	store_map_char(t_map *map, char *line)
{
	map->map[map->y][map->x] = line[map->x];
	if (line[map->x] == 'S' || line[map->x] == 'E' || line[map->x] == 'W'
		|| line[map->x] == 'N')
	{
		map->player_x = map->x;
		map->player_y = map->y;
	}
}

static void	map_copy(t_map *map, char *line)
{
	int	line_len;

	line_len = ft_strlen(line);
	map->x = 0;
	while (map->x < map->width)
	{
		if (map->x < line_len && line[map->x] && line[map->x] != '\n')
			store_map_char(map, line);
		else
			map->map[map->y][map->x] = 32;
		if (map->x < line_len && line[map->x] != '\n')
			map->tmp_map[map->y][map->x] = line[map->x];
		else
			map->tmp_map[map->y][map->x] = ' ';
		map->x++;
	}
	map->map[map->y][map->width] = '\0';
	map->tmp_map[map->y][map->width] = '\0';
	map->y++;
}

static void	map_alloc(t_map *map, char *av)
{
	int	i;

	i = 0;
	map->height = get_map_height(av);
	map->width = get_greater_width(av);
	map->map = malloc(sizeof(char *) * map->height);
	if (!map->map)
		return ;
	map->x = 0;
	map->y = 0;
	while (i < map->height)
	{
		map->map[i] = malloc(sizeof(char) * (map->width + 1));
		if (!map->map[i])
			return ;
		i++;
	}
}

void	read_from_map(t_game *game, t_map *map, char *av)
{
	char	*stash;
	char	*line;
	int		detect;

	stash = NULL;
	game->fd = open(av, O_RDONLY);
	if (game->fd < 0)
		return (ft_error(NULL, "file doesnt exist"));
	line = get_next_line(game->fd, &stash);
	map_alloc(map, av);
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
