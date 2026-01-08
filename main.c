/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:18:39 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/08 11:13:29 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_game	*game;

	game = NULL;
	if (ac != 2)
		return (ft_error(NULL, "wrong number of args"), 1);
	if (!check_arg_param(ac, av))
		return (1);
	game_init(&game);
	if (!game)
		return (1);
	if (!parse_identifer_line(game, av[1]))
		return (free_all(game), 1);
	return (free_all(game), 0);
}
