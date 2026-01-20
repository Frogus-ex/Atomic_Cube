/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:47:24 by aautret           #+#    #+#             */
/*   Updated: 2026/01/20 12:47:49 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3D.h"

/**
 * @brief Place un pixel couleur aux coordonnees donnees.
 * @param img image MLX cible
 * @param x abscisse en pixels
 * @param y ordonnee en pixels
 * @param color couleur ARGB
 */
void	my_put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	*(int *)(img->addr + offset) = color;
}