/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:56:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/13 17:29:13 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	if_draw(t_img *img, int y, int x)
{
	if (img->game->map[y][x] == WALL)
		mlx_put_image_to_window(img->game->mlx, img->game->win, img->wall,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (img->game->map[y][x] == PLAYER)
		mlx_put_image_to_window(img->game->mlx, img->game->win, img->player,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (img->game->map[y][x] == EXIT)
		mlx_put_image_to_window(img->game->mlx, img->game->win, img->exit,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (img->game->map[y][x] == COLLECT)
		mlx_put_image_to_window(img->game->mlx, img->game->win, img->collect,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (img->game->map[y][x] == FLOOR)
		mlx_put_image_to_window(img->game->mlx, img->game->win, img->floor,
			x * TILE_SIZE, y * TILE_SIZE);
}


void	draw_moves(t_game *game)
{
	char	*move_str;

	move_str = ft_itoa(game->player.moves);
	if (!move_str)
		ft_error(game, "ft_itoa a echoue");
	mlx_string_put(game->mlx, game->win, 10, 10, 0xCCFFFF, move_str);
	free(move_str);
}

void	draw_map(t_img *img)
{
	int		x;
	int		y;
	char	tile;

	y = 0;
	while (y < img->game->height)
	{
		x = 0;
		while (x < img->game->width)
		{
			tile = img->game->map[y][x];
			if_draw(img, y, x);
			x++;
		}
		y++;
	}
	draw_moves(img->game);
}
