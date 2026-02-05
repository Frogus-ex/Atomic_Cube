/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frogus <frogus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:25:04 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/05 10:46:21 by frogus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

int	init_mlx(t_game *game, t_map *map, t_img *img)
{
	if (!game || !map || !img)
		return (ft_error(game, "init_mlx: invalid pointers"), 0);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_error(game, "mlx_init failed"), 0);
	if (load_textures(game))
		return (0);
	img->width = SCREEN_WIDTH;
	img->height = SCREEN_HEIGHT;
	game->win = mlx_new_window(game->mlx, img->width, img->height, WND_NAME);
	if (!game->win)
		return (ft_error(game, "mlx_new_window failed"), 0);
	img->img = mlx_new_image(game->mlx, img->width, img->height);
	if (!img->img)
		return (ft_error(game, "mlx_new_image failed"), 0);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		return (ft_error(game, "mlx_get_data_addr failed"), 0);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_released, game);
	mlx_hook(game->win, 17, 0, cross_close, game);
	mlx_mouse_move(game->mlx, game->win, game->player->mouse_x,
		game->player->mouse_y);
	mlx_loop_hook(game->mlx, game_loop, game);
	return (1);
}
