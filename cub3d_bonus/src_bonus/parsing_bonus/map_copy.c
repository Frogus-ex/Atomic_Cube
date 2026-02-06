/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:38:28 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/06 11:21:33 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

static void	add_sprite_to_map(t_map *map)
{
	t_animate	**new_sprites;

	new_sprites = copy_sprites_array(map);
	if (!new_sprites)
		return ;
	animate_init(&new_sprites[map->sprite_count]);
	if (new_sprites[map->sprite_count])
	{
		new_sprites[map->sprite_count]->x = map->x;
		new_sprites[map->sprite_count]->y = map->y;
	}
	free(map->sprites);
	map->sprites = new_sprites;
	map->sprite_count++;
	if (!map->s_animate)
		map->s_animate = new_sprites[0];
}

static void	store_map_char(t_map *map, char *line)
{
	map->map[map->y][map->x] = line[map->x];
	store_player_position(map, line[map->x]);
	if (line[map->x] == 'A')
		add_sprite_to_map(map);
}

void	map_copy(t_map *map, char *line)
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
