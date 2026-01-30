/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:23:38 by aautret           #+#    #+#             */
/*   Updated: 2026/01/30 17:39:50 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3D.h"

typedef struct s_game	t_game;
typedef struct s_map	t_map;
typedef struct s_player	t_player;

typedef struct s_minimap {
	int	player_pos_x;
	int	player_pos_y;
} t_minimap;

/************************************************************************
 *								MINIMAP									*
 ***********************************************************************/

 // draw_minimap.c
void	draw_minimap(t_map *map, t_img *img);
int		check_colision(t_img *img, double px, double py);

#endif