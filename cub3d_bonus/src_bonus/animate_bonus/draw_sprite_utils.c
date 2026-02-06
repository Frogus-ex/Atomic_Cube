/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: autret <autret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:30:00 by autret            #+#    #+#             */
/*   Updated: 2026/02/05 16:35:14 by autret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

/**
 * @brief Vérifie si une couleur doit être considérée comme transparente
 * 
 * @param rgb Couleur RGB
 * @return 1 si transparent, 0 sinon
 */
int	is_transparent(int rgb)
{
	int	r;
	int	g;
	int	b;

	r = (rgb >> 16) & 0xFF;
	g = (rgb >> 8) & 0xFF;
	b = rgb & 0xFF;
	if (r > 245 && g < 10 && b > 245)
		return (1);
	if (r < 10 && g > 245 && b < 10)
		return (1);
	return (0);
}

/**
 * @brief Récupère la couleur d'un pixel du sprite avec gestion transparence
 */
int	get_sprite_pixel(void *img, int pos[2], t_animate *animate)
{
	t_mlx_data	mlx;
	int			color;
	int			rgb;

	mlx.data = mlx_get_data_addr(img, &mlx.bpp, &mlx.size_line, &mlx.endian);
	if (!mlx.data || pos[0] < 0 || pos[1] < 0
		|| pos[0] >= animate->frame_width || pos[1] >= animate->frame_height)
		return (-1);
	color = *(int *)(mlx.data + (pos[1] * mlx.size_line
				+ pos[0] * (mlx.bpp / 8)));
	rgb = color & 0x00FFFFFF;
	if (is_transparent(rgb))
		return (-1);
	return (color);
}
