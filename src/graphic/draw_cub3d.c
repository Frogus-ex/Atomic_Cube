/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:44:23 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/27 13:47:14 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_wall(t_img *img, int x, double wall_size)
{
	int	y;

	y = 0;
	img->wall_start = (img->height / 2) - (wall_size / 2);
	img->wall_end = (img->height / 2) + (wall_size / 2);
	while (y < img->height)
	{
		if (y < img->wall_start)
			my_put_pixel(img, x, y, 0xE11E00);
		else if (y < img->wall_end)
			my_put_pixel(img, x, y, 00000000);
			// draw_wall_text(img, x, y);
		else
			my_put_pixel(img, x, y, 0xDC6400);
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

void	draw_wall_text(t_img *img, int x, int y)
{
	
}
