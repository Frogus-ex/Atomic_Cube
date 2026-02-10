/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_cub3d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:52:39 by aautret           #+#    #+#             */
/*   Updated: 2026/02/10 10:45:49 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	player_init(t_player **player, t_game *game)
{
	*player = ft_calloc(1, sizeof(t_player));
	if (!*player)
		return (ft_error(NULL, "map init failed"));
	game->player = *player;
}

void	map_init(t_map **map)
{
	*map = ft_calloc(1, sizeof(t_map));
	if (!*map)
		return (ft_error(NULL, "map init failed"));
}

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
	(*game)->flag_players = 0;
	if (!(*game)->nbr_text)
	{
		ft_error(*game, "nbr_text allocation failed");
		*game = NULL;
		return ;
	}
	(*game)->nbr_line = 0;
}
