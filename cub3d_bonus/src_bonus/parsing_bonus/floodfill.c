/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:48:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/06 11:21:25 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

// alloue l espace memoire pour tmp_map

void	free_tmp_map(t_map *map)
{
	int	i;

	if (!map || !map->tmp_map)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->tmp_map[i]);
		i++;
	}
	free(map->tmp_map);
	map->tmp_map = NULL;
}

int	alloc_tmp_map(t_map *map)
{
	int	i;

	map->tmp_map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->tmp_map)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->tmp_map[i] = calloc(map->width + 1, sizeof(char));
		if (!map->tmp_map[i])
		{
			while (--i >= 0)
				free(map->tmp_map[i]);
			free(map->tmp_map);
			map->tmp_map = NULL;
			return (0);
		}
		i++;
	}
	map->tmp_map[map->height] = NULL;
	return (1);
}

void	fill(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
	{
		map->total_size = -1;
		return ;
	}
	if (map->tmp_map[y][x] == 'V' || map->tmp_map[y][x] == '1')
		return ;
	if (map->tmp_map[y][x] == ' ' || map->tmp_map[y][x] == '\0')
	{
		map->total_size = -1;
		return ;
	}
	if (map->tmp_map[y][x] != '0' && map->tmp_map[y][x] != 'N'
		&& map->tmp_map[y][x] != 'S' && map->tmp_map[y][x] != 'E'
		&& map->tmp_map[y][x] != 'W' && map->tmp_map[y][x] != 'D'
		&& map->tmp_map[y][x] != 'A')
	{
		map->total_size = -1;
		return ;
	}
	map->tmp_map[y][x] = 'V';
	fill(map, x, y + 1);
	fill(map, x, y - 1);
	fill(map, x + 1, y);
	fill(map, x - 1, y);
}

int	flood_fill(t_map *map)
{
	map->total_size = 0;
	fill(map, map->player_x, map->player_y);
	if (map->total_size == -1)
	{
		free_tmp_map(map);
		return (ft_error(NULL, "Map is invalid"), 1);
	}
	free_tmp_map(map);
	return (0);
}
