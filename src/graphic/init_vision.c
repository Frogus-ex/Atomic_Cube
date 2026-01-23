/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:36:27 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/23 11:15:19 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Calcul la distance du rayon entre le player et le mur et le stock dans
 * la structure img
 * 
 * @param img 
 */
void	get_distance(t_img *img, double xm, double ym)
{
	double	a;
	double	b;

	a = pow(xm - img->player->origin_x, 2);
	b = pow(ym - img->player->origin_y, 2);
	img->wall_distance = (int)sqrt(a + b);
}


// A REVOIR : ENDROIT OU STOCKE LE RAYON CAR IL EST RE-ECRASER A CHAQUE FOIS
