/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:38:02 by aautret           #+#    #+#             */
/*   Updated: 2026/02/05 13:36:48 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

int	load_sprite(t_game *game, t_animate *animate)
{
	int	i;
	int	width;
	int	height;

	i = 0;
	animate->frame[0] = mlx_xpm_file_to_image(game->mlx,
			"cub3d_bonus/animate_bonus/patronus_00.xpm", &width, &height);
	animate->frame[1] = mlx_xpm_file_to_image(game->mlx,
			"cub3d_bonus/animate_bonus/patronus_01.xpm", &width, &height);
	animate->frame[2] = mlx_xpm_file_to_image(game->mlx,
			"cub3d_bonus/animate_bonus/patronus_02.xpm", &width, &height);
	animate->frame[3] = mlx_xpm_file_to_image(game->mlx,
			"cub3d_bonus/animate_bonus/patronus_03.xpm", &width, &height);
	animate->frame[4] = mlx_xpm_file_to_image(game->mlx,
			"cub3d_bonus/animate_bonus/patronus_04.xpm", &width, &height);
	animate->frame[5] = mlx_xpm_file_to_image(game->mlx,
			"cub3d_bonus/animate_bonus/patronus_05.xpm", &width, &height);
	while (i < animate->frame_count)
	{
		if (!animate->frame[i])
			return (0);
		i++;
	}
	animate->frame_width = width;
	animate->frame_height = height;
	return (1);
}

/**
 * @brief 
 * 
 * - Accumuler le temps ecouler depuis le dernier appel
 * - Si assez de temps s'est écoulé (ex: 120ms)
 * - Boucle si on depasse la derniere frame
 * @param animate 
 * @param delta_ms 
 */
void	update_sprite_animation(t_animate *animate, int delta_ms)
{
	animate->acc_ms += delta_ms;
	if (animate->acc_ms >= animate->frame_ms)
	{
		animate->current_frame++;
		if (animate->current_frame >= animate->frame_count)
			animate->current_frame = 0;
		animate->acc_ms = 0;
	}
}
