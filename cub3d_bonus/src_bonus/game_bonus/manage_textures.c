/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:44:23 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/30 11:35:45 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

static char	*get_texture_data(t_img *img, double angle)
{
	if (img->texture->side == 0)
	{
		if (img->ray_dir_x > 0)
			return (img->texture->tex_ea_data);
		else
			return (img->texture->tex_we_data);
	}
	else
	{
		if (img->ray_dir_y > 0)
			return (img->texture->tex_so_data);
		else
			return (img->texture->tex_no_data);
	}
	(void)angle;
}

void	draw_wall_text(t_img *img, int x, int y, double angle)
{
	double	step;
	double	tex_pos;
	int		offset;
	int		color;
	char	*texture_data;

	texture_data = get_texture_data(img, angle);
	img->texture->tex_x = (int)(img->texture->wall_x * img->texture->tex_width);
	step = (double)img->texture->tex_height / img->wall_size;
	tex_pos = (y - img->wall_start) * step;
	img->texture->tex_y = (int)tex_pos;
	offset = img->texture->tex_y * img->texture->tex_line_len
		+ img->texture->tex_x * (img->texture->tex_bpp / 8);
	color = *(int *)(texture_data + offset);
	my_put_pixel(img, x, y, color);
}
