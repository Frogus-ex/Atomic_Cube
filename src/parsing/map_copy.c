/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:38:28 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/12 18:00:47 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	read_from_map(t_game *game, t_map *map, char *av)
{
	char	*stash;
	char	*line;
	int		detect;
	int		x;

	x = 0;
	stash = NULL;
	game->fd = open(av, O_RDONLY);
	if (game->fd < 0)
		return (ft_error(NULL, "file doesnt exist"));
	line = get_next_line(game->fd, &stash);
	map_alloc(map, av);
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

int	get_map_height(char *av)
{
	char	*line;
	char	*stash;
	int		fd;
	int		i;
	int		height;

	i = 0;
	height = 0;
	stash = NULL;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (free(stash), close(fd), 1);
	line = get_next_line(fd, &stash);
	if (!line)
		return (free(line), free(stash), close(fd), 1);
	while (line)
	{
		if (detector_start_map(line) == 1)
			height++;
		free(line);
		line = get_next_line(fd, &stash);
	}
	return (height);
}

int	get_greater_width(char *av)
{
	char	*line;
	char	*stash;
	int		fd;
	int		i;
	int		greater_width;

	i = 0;
	stash = NULL;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (free(stash), close(fd), 1);
	line = get_next_line(fd, &stash);
	if (!line)
		return (free(line), free(stash), close(fd), 1);
	greater_width = 0;
	while (line)
	{
		while (line[i] && detector_start_map(line) == 1)
			i++;
		if (greater_width < 1)
			greater_width = i;
		free(line);
		line = get_next_line(fd, &stash);
	}
	return (greater_width);
}

void	map_alloc(t_map *map, char *av)
{
	int	i;

	i = 0;
	map->height = get_map_height(av);
	map->width = get_greater_width(av);
	map->total_size = (map->height) * (map->width);
	map->map = malloc(sizeof(char *) * map->height);
	map->x = 0;
	map->y = 0;
	if (!map->map)
		return ;
	while (i < map->height)
	{
		map->map[i] = malloc(sizeof(char) * (map->width + 1));
		if (!map->map[i])
			return ;
		i++;
	}
}

void	map_copy(t_map *map, char *line)
{
	map->x = 0;
	while (map->x < map->width)
	{
		if (line[map->x])
			map->map[map->y][map->x] = line[map->x];
		else
			map->map[map->y][map->x] = 0;
		map->x++;
	}
	printf("%s",map->map[map->y]);
	map->y++;
}
