/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frogus <frogus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:18:39 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/07 13:25:03 by frogus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_game	*game;

	game = NULL;
	if (ac != 2)
		ft_error(NULL, "wrong number of args");
	check_arg_param(ac, av);
	game_init(&game);
	if (!game)
		return (1);
	parse_identifer_line(game, av[1]);
	return (0);
}
