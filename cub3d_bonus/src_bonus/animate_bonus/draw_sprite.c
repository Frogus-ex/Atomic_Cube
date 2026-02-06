/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: autret <autret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:00:00 by aautret           #+#    #+#             */
/*   Updated: 2026/02/05 17:28:55 by autret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

/**
 * @brief Calcule les paramètres de projection du sprite
 * 
 * @param sprite Structure contenant position x, y, screen_x, distance, etc.
 * @param img Structure image avec player
 */
static void	calculate_sprite_projection(t_sprite_proj *sprite, t_img *img,
	t_animate *animate)
{
	double	sprite_dx;
	double	sprite_dy;
	double	sprite_angle;
	double	relative_angle;
	double	aspect_ratio;

	sprite_dx = animate->x - img->player->origin_x;
	sprite_dy = animate->y - img->player->origin_y;
	sprite->distance = sqrt(sprite_dx * sprite_dx + sprite_dy * sprite_dy);
	if (sprite->distance < 1.0)
		sprite->distance = 1.0;
	sprite_angle = atan2(sprite_dy, sprite_dx);
	relative_angle = sprite_angle - img->player->direction_vue;
	while (relative_angle > M_PI)
		relative_angle -= 2 * M_PI;
	while (relative_angle < -M_PI)
		relative_angle += 2 * M_PI;
	sprite->sprite_height = (int)((SCREEN_HEIGHT / sprite->distance)
			* TILE_SIZE * 0.5);
	aspect_ratio = (double)animate->frame_width / (double)animate->frame_height;
	sprite->sprite_width = (int)(sprite->sprite_height * aspect_ratio);
	sprite->screen_x = (int)((relative_angle / FOV + 0.5) * SCREEN_WIDTH)
		- sprite->sprite_width / 2;
}

static void	draw_sprite_pixel(t_img *img, t_animate *animate,
	t_sprite_proj *sprite, int pos[4])
{
	int	tex_pos[2];
	int	color;

	if (sprite->screen_x + pos[2] >= 0
		&& sprite->screen_x + pos[2] < SCREEN_WIDTH && pos[3] >= 0)
	{
		tex_pos[0] = (pos[2] * animate->frame_width) / sprite->sprite_width;
		tex_pos[1] = (pos[0] * animate->frame_height) / sprite->sprite_height;
		color = get_sprite_pixel(animate->frame[animate->current_frame],
				tex_pos, animate);
		if (color != -1)
			my_put_pixel(img, sprite->screen_x + pos[2], pos[3], color);
	}
}

static void	draw_sprite_line(t_img *img, t_animate *animate,
	t_sprite_proj *sprite, int pos[2])
{
	int	sprite_x;
	int	coords[4];

	sprite_x = 0;
	while (sprite_x < sprite->sprite_width)
	{
		coords[0] = pos[0];
		coords[1] = pos[1];
		coords[2] = sprite_x;
		coords[3] = pos[1] + pos[0];
		draw_sprite_pixel(img, animate, sprite, coords);
		sprite_x++;
	}
}

/**
 * @brief Dessine le sprite en 3D dans le rendu
 */
void	draw_sprite_3d(t_game *game, t_img *img, t_animate *animate)
{
	t_sprite_proj	sprite;
	int				pos[2];

	(void)game;
	if (!animate || !animate->frame[animate->current_frame])
		return ;
	calculate_sprite_projection(&sprite, img, animate);
	if (sprite.screen_x < -sprite.sprite_width
		|| sprite.screen_x >= SCREEN_WIDTH + sprite.sprite_width)
		return ;
	pos[1] = (SCREEN_HEIGHT - sprite.sprite_height) / 2;
	pos[0] = 0;
	while (pos[0] < sprite.sprite_height
		&& pos[1] + pos[0] < SCREEN_HEIGHT)
	{
		draw_sprite_line(img, animate, &sprite, pos);
		pos[0]++;
	}
}
