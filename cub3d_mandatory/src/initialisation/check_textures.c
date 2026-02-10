/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:50:52 by tlorette          #+#    #+#             */
/*   Updated: 2026/02/10 13:06:44 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_texture_file(char *path)
{
	int	fd;

	if (!path)
		return (ft_error(NULL, "texture path is NULL"), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	validate_all_textures(t_game *game)
{
	if (!check_texture_file(game->no_text))
		return (0);
	if (!check_texture_file(game->so_text))
		return (0);
	if (!check_texture_file(game->ea_text))
		return (0);
	if (!check_texture_file(game->we_text))
		return (0);
	return (1);
}
