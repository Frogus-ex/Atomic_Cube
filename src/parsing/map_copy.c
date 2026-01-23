/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:38:28 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/23 11:21:27 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
		return (free(line), free(stash), close(game->fd),
			ft_error(game, "tmp_map allocation failed"));
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
		if (detector_start_map(line) == 1)
		{
			i = 0;
			while (line[i])
				i++;
			if (i > greater_width)
				greater_width = i;
		}
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

void	map_copy(t_map *map, char *line)
{
	int	line_len;

	line_len = ft_strlen(line);
	map->x = 0;
	while (map->x < map->width)
	{
		if (map->x < line_len && line[map->x] && line[map->x] != '\n')
		{
			map->map[map->y][map->x] = line[map->x];
			if (line[map->x] == 'S' || line[map->x] == 'E'
				|| line[map->x] == 'W' || line[map->x] == 'N')
			{
				map->player_x = map->x;
				map->player_y = map->y;
			}
		}
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
