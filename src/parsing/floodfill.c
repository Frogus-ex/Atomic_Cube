/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:48:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/20 16:13:32 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//alloue l espace memoire pour tmp_map

void	alloc_tmp_map(t_map *map)
{
	int	i;

	map->tmp_map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->tmp_map)
		return ;
	i = 0;
	while (i < map->height)
	{
		map->tmp_map[i] = calloc(map->width + 1, sizeof(char));
		if (!map->tmp_map[i])
			return ;
		i++;
	}
	map->tmp_map[map->height] = NULL;
}

void	tmp_map_copy(t_map *map, char *line)
{
	int	len;

	len = 0;
	while (line[len])
		len++;
	map->x = 0;
	while (map->x < map->width)
	{
		if (map->x < len && line[map->x] != ' ')
			map->tmp_map[map->y][map->x] = line[map->x];
		else
			map->tmp_map[map->y][map->x] = '\0';
		map->x++;
	}
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
		&& map->tmp_map[y][x] != 'W')
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

// void	print_map(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	printf("\n=== MAP AFTER FLOOD FILL ===\n");
// 	i = 0;
// 	while (i < map->height)
// 	{
// 		j = 0;
// 		while (j < map->width)
// 		{
// 			if (map->tmp_map[i][j] == '\0')
// 				printf(" ");
// 			else
// 				printf("%c", map->tmp_map[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// 	printf("===========================\n\n");
// }

int	flood_fill(t_map *map)
{
	map->total_size = 0;
	fill(map, map->player_x, map->player_y);
	if (map->total_size == -1)
		return (ft_error(NULL, "Map is invalid"), 1);
	return (0);
}
