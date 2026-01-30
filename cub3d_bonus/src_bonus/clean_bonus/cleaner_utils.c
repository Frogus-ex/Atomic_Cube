/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:44:42 by aautret           #+#    #+#             */
/*   Updated: 2026/01/30 11:10:10 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

void	free_texture_in_game(t_game *game)
{
	if (game->textures->tex_no_img && game->mlx)
		mlx_destroy_image(game->mlx, game->textures->tex_no_img);
	if (game->textures->tex_so_img && game->mlx)
		mlx_destroy_image(game->mlx, game->textures->tex_so_img);
	if (game->textures->tex_ea_img && game->mlx)
		mlx_destroy_image(game->mlx, game->textures->tex_ea_img);
	if (game->textures->tex_we_img && game->mlx)
		mlx_destroy_image(game->mlx, game->textures->tex_we_img);
	free(game->textures);
}
