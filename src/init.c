/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:25:04 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/14 14:03:23 by tlorette         ###   ########.fr       */
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
		return (ft_error(NULL, "map init failed"));
}

void	img_init(t_img **img)
{
	*img = ft_calloc(1, sizeof(t_img));
	if (!*img)
		return (ft_error(NULL, "img init failed"));
}

void	player_init(t_player **player)
{
	*player = ft_calloc(1, sizeof(t_player));
	if (!*player)
		return (ft_error(NULL, "map init failed"));
}

void	init_mlx(t_game *game, t_map *map, t_img *img)
{
	if (!game || !map || !img)
		return (ft_error(game, "init_mlx: invalid pointers"));
	else
	{
		img->width = TILE_SIZE * map->width;
		img->height = TILE_SIZE * map->height;
	}
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_error(game, "mlx_init failed"));
	mlx_get_screen_size(game->mlx, &img->screen_width, &img->screen_height);
	if (img->width > img->screen_width || img->height > img->screen_height)
	{
		img->width = img->screen_width - 100;
		img->height = img->screen_height - 100;
	}
	game->win = mlx_new_window(game->mlx, img->width, img->height, WND_NAME);
	if (!game->win)
		return (ft_error(game, "mlx_new_window failed"));
	img->img = mlx_new_image(game->mlx, img->width, img->height);
	if (!img->img)
		return (ft_error(game, "mlx_new_image failed"));
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		return (ft_error(game, "mlx_get_data_addr failed"));
	mlx_hook(game->win, 2, 1L << 0, player_input, img);
	mlx_hook(game->win, 17, 0, cross_close, game);
}
