/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:25:04 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/29 13:35:15 by tlorette         ###   ########.fr       */
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
	(*game)->flag_players = 0;
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

void	img_init(t_img **img, t_game *game)
{
	*img = ft_calloc(1, sizeof(t_img));
	if (!*img)
		return (ft_error(NULL, "img init failed"));
	(*img)->texture = game->textures;
}

void	player_init(t_player **player, t_game *game)
{
	*player = ft_calloc(1, sizeof(t_player));
	if (!*player)
		return (ft_error(NULL, "map init failed"));
	game->player = *player;
}

void	text_init(t_texture **text)
{
	*text = ft_calloc(1, sizeof(t_texture));
	if (!*text)
		return (ft_error(NULL, "map init failed"));
}

void	init_ray_params(t_ray_params *params)
{
	params->ray_hit_x = 0;
	params->ray_hit_y = 0;
	params->step_x = 0;
	params->step_y = 0;
	params->map_x = 0;
	params->map_y = 0;
	params->found_wall = 0;
	params->distance = 0;
}

int	init_mlx(t_game *game, t_map *map, t_img *img)
{
	if (!game || !map || !img)
		return (ft_error(game, "init_mlx: invalid pointers"), 0);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_error(game, "mlx_init failed"), 0);
	load_textures(game);
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
	mlx_loop_hook(game->mlx, player_input, game);
	return (1);
}
