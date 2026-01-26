/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frogus <frogus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:44:23 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/26 16:21:57 by frogus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_wall(t_img *img, int x, double wall_size)
{
	double	wall_start;
	double	wall_end;
	int		y;

	y = 0;
	wall_start = (img->height / 2) - (wall_size / 2);
	wall_end = (img->height / 2) + (wall_size / 2);
	while (y < img->height)
	{
		if (y < wall_start)
			my_put_pixel(img, x, y, 0xE11E00);
		else if (y < wall_end)
			my_put_pixel(img, x, y, 0xDC6400);
		else
			my_put_pixel(img, x, y, 0xFFFF00);
		y++;
	}
}

void	load_textures(t_game *game)
{
	int		width;
	int		height;

	game->textures->tex_no_img = mlx_xpm_file_to_image(game->mlx,
			game->no_text, &width, &height);
	if (!game->textures->tex_no_img)
		ft_error(game, "Failed to load North texture");
	game->textures->tex_no_data = mlx_get_data_addr(game->textures->tex_no_img,
			&game->textures->tex_bpp, &game->textures->tex_line_len,
			&game->textures->tex_endian);
	game->textures->tex_so_img = mlx_xpm_file_to_image(game->mlx,
			game->so_text, &width, &height);
	if (!game->textures->tex_so_img)
		ft_error(game, "Failed to load South texture");
	game->textures->tex_so_data = mlx_get_data_addr(game->textures->tex_so_img,
			&game->textures->tex_bpp, &game->textures->tex_line_len,
			&game->textures->tex_endian);
	game->textures->tex_ea_img = mlx_xpm_file_to_image(game->mlx,
			game->ea_text, &width, &height);
	if (!game->textures->tex_ea_img)
		ft_error(game, "Failed to load East texture");
	game->textures->tex_ea_data = mlx_get_data_addr(game->textures->tex_ea_img,
			&game->textures->tex_bpp, &game->textures->tex_line_len,
			&game->textures->tex_endian);
	game->textures->tex_we_img = mlx_xpm_file_to_image(game->mlx,
			game->we_text, &width, &height);
	if (!game->textures->tex_we_img)
		ft_error(game, "Failed to load West texture");
	game->textures->tex_we_data = mlx_get_data_addr(game->textures->tex_we_img,
			&game->textures->tex_bpp, &game->textures->tex_line_len,
			&game->textures->tex_endian);
	game->textures->tex_width = width;
	game->textures->tex_height = height;
}
