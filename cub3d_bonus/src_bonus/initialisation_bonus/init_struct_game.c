/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_game.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:55:26 by aautret           #+#    #+#             */
/*   Updated: 2026/01/30 11:12:00 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

void	text_init(t_texture **text)
{
	*text = ft_calloc(1, sizeof(t_texture));
	if (!*text)
		return (ft_error(NULL, "map init failed"));
}

void	img_init(t_img **img, t_game *game)
{
	*img = ft_calloc(1, sizeof(t_img));
	if (!*img)
		return (ft_error(NULL, "img init failed"));
	(*img)->texture = game->textures;
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
	params->is_horizontal = 0;
}

int	load_textures(t_game *game)
{
	return (load_single_texture(game, game->no_text,
			(void **)&game->textures->tex_no_img, &game->textures->tex_no_data)
		|| load_single_texture(game, game->so_text,
			(void **)&game->textures->tex_so_img, &game->textures->tex_so_data)
		|| load_single_texture(game, game->ea_text,
			(void **)&game->textures->tex_ea_img, &game->textures->tex_ea_data)
		|| load_single_texture(game, game->we_text,
			(void **)&game->textures->tex_we_img,
			&game->textures->tex_we_data));
}
