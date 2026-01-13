/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:25:04 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/13 17:25:22 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	game_init(t_game **game)
{
	*game = ft_calloc(1, sizeof(t_game));
	if (!*game)
	{
		ft_error(NULL, "game allocation failed");
		return ;
	}
	(*game)->mlx = NULL;
	(*game)->win = NULL;
	(*game)->fd = -1;
	(*game)->nbr_text = ft_calloc(6, sizeof(int));
	if (!(*game)->nbr_text)
	{
		ft_error(*game, "nbr_text allocation failed");
		*game = NULL;
		return ;
	}
	(*game)->nbr_line = 0;
}

void	map_init(t_map **map)
{
	*map = ft_calloc(1, sizeof(t_map));
	if (!*map)
		return (ft_error(NULL, "malloc failed"));
}

void	init_mlx(t_game *game, t_map *map, t_img *img)
{
	map->width = TILE_SIZE * map->width;
	map->height = TILE_SIZE * map->height;
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error(game, "mlx_init echoue");
	// load_texture(game, img);
	mlx_get_screen_size(game->mlx, &img->screen_width, &img->screen_height);
	if (img->width > img->screen_width || img->height > img->screen_height)
		ft_error(game, "map trop grande");
	game->win = mlx_new_window(game->mlx, img->width, img->height, WND_NAME);
	img->img = mlx_new_image(game->mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}
