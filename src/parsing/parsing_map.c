/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:20:20 by aautret           #+#    #+#             */
/*   Updated: 2026/01/16 12:52:36 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	parse_map_line(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("10NSEW \n", line[i]))
			return (printf("error: invalid caracter detected \n"), 1);
		if (ft_strchr("NSEW", line[i]) && game->flag_players == 1)
			return (printf("error: invalid number of players in map\n"), 1);
		else if (ft_strchr("NSEW", line[i]) && game->flag_players == 0)
			game->flag_players = 1;
		i++;
	}
	return (0);
}

