/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:25:04 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/12 14:22:13 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	game_init(t_game **game)
{
	*game = ft_calloc(1, sizeof(t_game));
	if (!*game)
	{
		ft_error(NULL, "game allocation failed");
		return ;
	}
	(*game)->mlx = NULL;
	(*game)->win = NULL;
	(*game)->fd = -1;
	(*game)->nbr_text = ft_calloc(6, sizeof(int));
	if (!(*game)->nbr_text)
	{
		ft_error(*game, "nbr_text allocation failed");
		*game = NULL;
		return ;
	}
	(*game)->nbr_line = 0;
}

void	map_init(t_map **map)
{
	*map = ft_calloc(1, sizeof(t_map));
	if (!*map)
		return (ft_error(NULL, "malloc failed"));
}
