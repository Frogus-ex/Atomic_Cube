/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:56:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/28 13:45:06 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Vérifie si une position (en pixels) est franchissable (pas de mur).
 * Teste les bornes, convertit en coordonnées de tuile et vérifie la
 * présence d'un mur ('1') dans la grille.
 * 
 * @param img
 * @param px Coordonnée X en pixels à tester.
 * @param py Coordonnée Y en pixels à tester.
 * @return int 1 si la position est libre (pas de mur), 0 sinon.
 * @note Renvoie 0 aussi en cas d'arguments invalides ou hors limites.
 */
static int	check_colision(t_img *img, double px, double py)
{
	int	tx;
	int	ty;

	if (!img || !img->map || !img->map->map || px < 0 || py < 0)
		return (0);
	tx = (int)floor(px / TILE_SIZE);
	ty = (int)floor(py / TILE_SIZE);
	if (ty < 0 || ty >= img->map->height || tx < 0 || tx >= img->map->width)
		return (0);
	if (!img->map->map[ty] || !img->map->map[ty][tx])
		return (0);
	if (img->map->map[ty][tx] == '1')
		return (0);
	return (1);
}

/**
 * @brief Trace un seul rayon pour un angle donné et affiche la colonne.
 * 
 * Calcule un pas le long du rayon depuis la position du joueur jusqu'à la
 * distance maximale, teste les collisions tuile par tuile, récupère la face
 * touchée (get_wall_hit), calcule la distance corrigée (get_distance)
 * puis dessine la colonne correspondante (draw_wall).
 * 
 * @param img
 * @param angle Angle du rayon en radians.
 * @param collumn Indice de colonne écran (coordonnée X) à dessiner.
 * @note Fonction interne statique / arrête le raycast dès la première collision.
 */
static void	draw_angle_new(t_img *img, double angle, int collumn)
{
	double	step_x;
	double	step_y;
	double	current_x;
	double	current_y;
	int		i;

	if (!img || !img->player)
		return ;
	img->player->view_angle = img->player->direction_vue + (-M_PI / 8);
	img->distance_x = img->player->origin_x + 110 * cos(angle);
	img->distance_y = img->player->origin_y + 110 * sin(angle);
	step_x = (img->distance_x - img->player->origin_x) / 110;
	step_y = (img->distance_y - img->player->origin_y) / 110;
	i = 0;
	while (i < find_biggest(img))
	{
		current_x = img->player->origin_x + step_x * i;
		current_y = img->player->origin_y + step_y * i;
		if (!check_colision(img, current_x, current_y))
		{
			get_wall_hit(img->texture, current_x, current_y);
			get_distance(img, current_x, current_y, angle);
			draw_wall(img, collumn, img->wall_size, angle);
			break ;
		}
		i++;
	}
}

/**
 * @brief Balaye l'écran par colonnes et appelle le traceur de rayon.
 * 
 * Calcule l'incrément d'angle en fonction de img->width (résolution horizontale)
 * et itère sur chaque colonne pour lancer draw_angle_new.
 * 
 * @param img
 * @note Met en place l'intervalle d'angles centré sur player->direction_vue.
 */
static void	calc_and_draw_angle(t_img *img)
{
	double	angle_step;
	double	angle;
	int		i;

	i = 0;
	angle_step = (M_PI / 4) / img->width;
	while (i < img->width)
	{
		angle = img->player->direction_vue - (M_PI / 8) + (i * angle_step);
		draw_angle_new(img, angle, i);
		i++;
	}
}

/**
 * @brief Redessine la scène (mini-map / rayons / murs) et affiche l'image.
 * 
 * Lance le calcul et le rendu des rayons, puis pousse l'image résultante vers
 * la fenêtre via mlx_put_image_to_window.
 * 
 * @param img
 */
void	put_cub3d_to_wnd(t_img *img)
{
	calc_and_draw_angle(img);
	mlx_put_image_to_window(img->game->mlx, img->game->win, img->img, 0, 0);
}
