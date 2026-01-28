/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:44:23 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/28 13:45:31 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_wall(t_img *img, int x, double wall_size, double angle)
{
	int	y;

	y = 0;
	img->wall_start = (img->height / 2) - (wall_size / 2);
	img->wall_end = (img->height / 2) + (wall_size / 2);
	while (y < img->height)
	{
		if (y < img->wall_start)
			my_put_pixel(img, x, y, 0x3D2817);
		else if (y < img->wall_end)
			draw_wall_text(img, x, y, angle);
		else
			my_put_pixel(img, x, y, 0x2F2F2F);
		y++;
	}
}

void	load_textures(t_game *game)
{
	int	width;
	int	height;

	game->textures->tex_no_img = mlx_xpm_file_to_image(game->mlx, game->no_text,
			&width, &height);
	if (!game->textures->tex_no_img)
		ft_error(game, "Failed to load North texture");
	game->textures->tex_no_data = mlx_get_data_addr(game->textures->tex_no_img,
			&game->textures->tex_bpp, &game->textures->tex_line_len,
			&game->textures->tex_endian);
	game->textures->tex_so_img = mlx_xpm_file_to_image(game->mlx, game->so_text,
			&width, &height);
	if (!game->textures->tex_so_img)
		ft_error(game, "Failed to load South texture");
	game->textures->tex_so_data = mlx_get_data_addr(game->textures->tex_so_img,
			&game->textures->tex_bpp, &game->textures->tex_line_len,
			&game->textures->tex_endian);
	game->textures->tex_ea_img = mlx_xpm_file_to_image(game->mlx, game->ea_text,
			&width, &height);
	if (!game->textures->tex_ea_img)
		ft_error(game, "Failed to load East texture");
	game->textures->tex_ea_data = mlx_get_data_addr(game->textures->tex_ea_img,
			&game->textures->tex_bpp, &game->textures->tex_line_len,
			&game->textures->tex_endian);
	game->textures->tex_we_img = mlx_xpm_file_to_image(game->mlx, game->we_text,
			&width, &height);
	if (!game->textures->tex_we_img)
		ft_error(game, "Failed to load West texture");
	game->textures->tex_we_data = mlx_get_data_addr(game->textures->tex_we_img,
			&game->textures->tex_bpp, &game->textures->tex_line_len,
			&game->textures->tex_endian);
	game->textures->tex_width = width;
	game->textures->tex_height = height;
}

static char	*get_texture_data(t_img *img, double angle)
{
	img->ray_dir_x = cos(angle);
	img->ray_dir_y = sin(angle);
	if (img->texture->side == 0)
	{
		if (img->ray_dir_x > 0)
			return (img->texture->tex_we_data);
		else
			return (img->texture->tex_ea_data);
	}
	else
	{
		if (img->ray_dir_y > 0)
			return (img->texture->tex_no_data);
		else
			return (img->texture->tex_so_data);
	}
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
