/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_cub3d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:52:39 by aautret           #+#    #+#             */
/*   Updated: 2026/02/05 13:36:48 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

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

void	minimap_init(t_minimap **minimap)
{
	*minimap = ft_calloc(1, sizeof(t_minimap));
	if (!*minimap)
		return (ft_error(NULL, "minimap init failed"));
	(*minimap)->player_pos_x = 0;
	(*minimap)->player_pos_y = 0;
}

void	animate_init(t_animate **animate)
{
	int	i;

	*animate = ft_calloc(1, sizeof(t_animate));
	if (!*animate)
		return (ft_error(NULL, "animate init failed"));
	(*animate)->frame_ms = 120;
	(*animate)->frame_count = 6;
	(*animate)->current_frame = 0;
	(*animate)->acc_ms = 0;
	(*animate)->x = -1;
	(*animate)->y = -1;
	i = 0;
	while (i < 6)
	{
		(*animate)->frame[i] = NULL;
		i++;
	}
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
