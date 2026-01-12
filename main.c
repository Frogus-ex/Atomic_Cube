/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:18:39 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/12 16:34:22 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_game	*game;
	t_map	*map;

	game = NULL;
	map = NULL;
	if (ac != 2)
		return (ft_error(NULL, "wrong number of args"), 1);
	game_init(&game);
	if (!game)
		return (1);
	map_init(&map);
	if (!map)
		return (free(game), 1);
	if (parsing(game, av[1]))
		return (free_all(game), 1);
	read_from_map(game, map, av[1]);
	return (free(map), free_all(game), 0);
}
