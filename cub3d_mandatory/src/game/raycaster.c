/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:51:15 by aautret           #+#    #+#             */
/*   Updated: 2026/01/28 15:06:15 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Détermine quelle face du mur a été touchée et calcule la position
 *
 * Détecte si le hit est sur un bord vertical ou horizontal de la tuile
 * et stocke la fraction (0.0 - 1.0) dans texture->wall_x.
 *
 * @param texture
 * @param current_x Position X (en pixels) du point de collision.
 * @param current_y Position Y (en pixels) du point de collision.
 * @note Utilise TILE_SIZE pour calculer la position intra-tile.
 *
 */
void	get_wall_hit(t_texture *texture, double current_x, double current_y)
{
	double	x_in_tile;
	double	y_in_tile;

	x_in_tile = fmod(current_x, TILE_SIZE);
	y_in_tile = fmod(current_y, TILE_SIZE);
	if (x_in_tile < 1.0 || x_in_tile > TILE_SIZE - 1.0)
		texture->side = 0;
	else
		texture->side = 1;
	if (texture->side == 0)
		texture->wall_x = fmod(current_y, TILE_SIZE) / TILE_SIZE;
	else
		texture->wall_x = fmod(current_x, TILE_SIZE) / TILE_SIZE;
}

/**
 * @brief Calcule la distance entre le joueur et le point de collision, corrige
 *  l'effet de fish-eye et met à jour la taille de mur projetée.
 *
 * Calcule la distance entre (xm,ym) et l'origine du joueur,
 * applique la correction angulaire via cos(angle - img->player->view_angle)
 * et met img->wall_distance et img->wall_size.
 *
 * @param img
 * @param xm Coordonnée X (en pixels) du point de collision.
 * @param ym Coordonnée Y (en pixels) du point de collision.
 * @param angle Angle du rayon (en radians) utilisé.
 *
 * @param img
 */
void	get_distance(t_img *img, double xm, double ym, double angle)
{
	double	a;
	double	b;

	a = pow(xm - img->player->origin_x, 2);
	b = pow(ym - img->player->origin_y, 2);
	img->wall_distance = sqrt(a + b);
	img->wall_distance *= cos(angle - img->player->view_angle);
	if (img->wall_distance <= 0.1)
		return ;
	img->wall_size = (img->height / img->wall_distance) * TILE_SIZE;
}

/**
 * @brief Rendu vertical d'une colonne de l'écran correspondant à un mur.
 *
 * Calcule wall_start et wall_end sur l'axe Y à partir de wall_size puis :
 *
 * - dessine le plafond au-dessus,
 * - dessine la portion texturée du mur via draw_wall_text,
 * - dessine le sol (couleur fixe) en dessous.
 *
 * @param img
 * @param x Indice de colonne (coordonnée X écran) à dessiner.
 * @param wall_size Hauteur projetée du mur (en pixels) pour cette colonne.
 * @param angle Angle du rayon correspondant (en radians) pour l'échantillonnage
 * @note draw_wall_text est appelé pour chaque pixel de la portion murale

 *
 * @param img
 * @param x
 * @param wall_size
 * @param angle
 */
void	draw_wall(t_img *img, int x, double wall_size, double angle)
{
	int	y;
	int	color_f;
	int	color_c;

	y = 0;
	img->wall_start = (img->height / 2) - (wall_size / 2);
	img->wall_end = (img->height / 2) + (wall_size / 2);
	color_c = ft_atoi(img->game->c_text);
	color_f = ft_atoi(img->game->f_text);
	while (y < img->height)
	{
		if (y < img->wall_start)
			my_put_pixel(img, x, y, color_f);
		else if (y < img->wall_end)
			draw_wall_text(img, x, y, angle);
		else
			my_put_pixel(img, x, y, color_c);
		y++;
	}
}
