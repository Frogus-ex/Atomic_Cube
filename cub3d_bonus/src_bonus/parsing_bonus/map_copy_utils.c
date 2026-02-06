/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copy_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:15:08 by aautret           #+#    #+#             */
/*   Updated: 2026/02/06 13:28:23 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

static void	get_greater_width_utils(char *line, int *greater_width)
{
	int	i;

	if (detector_start_map(line) == 1)
	{
		i = 0;
		while (line[i])
			i++;
		if (i > *greater_width)
			*greater_width = i;
	}
}

int	get_greater_width(char *av)
{
	char	*line;
	char	*stash;

	stash = NULL;
	int (fd) = open(av, O_RDONLY);
	if (fd < 0)
		return (free(stash), close(fd), 1);
	line = get_next_line(fd, &stash);
	if (!line)
		return (free(line), free(stash), close(fd), 1);
	int (greater_width) = 0;
	while (line)
	{
		get_greater_width_utils(line, &greater_width);
		free(line);
		line = get_next_line(fd, &stash);
	}
	return (greater_width);
}

int	get_map_height(char *av)
{
	char	*line;
	char	*stash;
	int		fd;
	int		height;

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

void	store_player_position(t_map *map, char c)
{
	if (c == 'S' || c == 'E' || c == 'W' || c == 'N')
	{
		map->player_x = map->x;
		map->player_y = map->y;
	}
}

t_animate	**copy_sprites_array(t_map *map)
{
	t_animate	**new_sprites;
	int			i;

	new_sprites = ft_calloc(map->sprite_count + 2, sizeof(t_animate *));
	if (!new_sprites)
		return (NULL);
	i = 0;
	while (i < map->sprite_count)
	{
		new_sprites[i] = map->sprites[i];
		i++;
	}
	return (new_sprites);
}
