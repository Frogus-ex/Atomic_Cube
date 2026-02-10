/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:25:04 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/10 13:16:37 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

/**
 * @brief Initialise MLX et charge les textures
 *
 * @param game
 * @param img
 * @return int
 */
static int	init_mlx_base(t_game *game, t_img *img)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_error(game, "mlx_init failed"), 0);
	if (load_textures(game))
		return (ft_error(NULL, "texture failed to load"), 0);
	img->width = SCREEN_WIDTH;
	img->height = SCREEN_HEIGHT;
	return (1);
}

/**
 * @brief Crée la fenêtre et l'image MLX
 *
 * @param game
 * @param img
 * @return int
 */
static int	create_window_and_image(t_game *game, t_img *img)
{
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
	return (1);
}

/**
 * @brief Configure les hooks MLX (clavier, souris, loop)
 * 
 * @param game 
 */
static void	set_up_mlx_hook(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_released, game);
	mlx_hook(game->win, 17, 0, cross_close, game);
	mlx_mouse_move(game->mlx, game->win, game->player->mouse_x,
		game->player->mouse_y);
	mlx_loop_hook(game->mlx, game_loop, game);
}

/**
 * @brief  Initialise MLX, fenêtre, image et hooks
 * 
 * @param game Structure du jeu
 * @param map Structure de la map
 * @param img Strucutre de l'image
 * @return int 
 */
int	init_mlx(t_game *game, t_map *map, t_img *img)
{
	if (!game || !map || !img)
		return (ft_error(game, "init_mlx: invalid pointers"), 0);
	if (!init_mlx_base(game, img))
		return (0);
	if (!create_window_and_image(game, img))
		return (0);
	set_up_mlx_hook(game);
	return (1);
}
