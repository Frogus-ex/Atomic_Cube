/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:18:39 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/07 16:18:38 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_game	*game;

	game = NULL;
	if (ac != 2)
		ft_error("wrong number of args");
	check_arg_param(ac, av);
	game_init(&game, av[1]);
	if (!game)
		return (1);
	if (parsing(game, av[1]) == 0)
		return (printf("PARSING SUCCESS\n"), 0);
	else
		return (printf("PARSING FAILDED\n"), 1);
	return (0);
}
