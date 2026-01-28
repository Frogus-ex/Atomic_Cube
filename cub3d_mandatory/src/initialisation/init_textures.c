/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:44:23 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/28 14:06:19 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief Récupère et stocke le chemin de la texture Ouest (WE)
 *
 * @param game
 * @param line
 * @param i
 */
void	grab_we_text(t_game *game, char *line, int i)
{
	int	y;

	y = 0;
	if (game->nbr_text[2] != 0)
		return ;
	while (line && line[i] == 32)
		i++;
	game->we_text = malloc((ft_strlen(line) - i) + 1);
	while (line[i] && line[i] != '\n')
		game->we_text[y++] = line[i++];
	game->we_text[y] = '\0';
	game->nbr_text[2]++;
}

/**
 * @brief Récupère et stocke le chemin de la texture Est (EA)
 *
 * @param game
 * @param line
 * @param i
 */
void	grab_ea_text(t_game *game, char *line, int i)
{
	int	y;

	y = 0;
	if (game->nbr_text[3] != 0)
		return ;
	while (line && line[i] == 32)
		i++;
	game->ea_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && line[i] != '\n')
		game->ea_text[y++] = line[i++];
	game->ea_text[y] = '\0';
	game->nbr_text[3]++;
}

/**
 * @brief Récupère et stocke la couleur du sol (F)
 *
 * @param game
 * @param line
 * @param i
 */
void	grab_f_text(t_game *game, char *line, int i)
{
	int	y;

	y = 0;
	if (game->nbr_text[4] != 0)
		return ;
	while (line && line[i] == 32)
		i++;
	game->f_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && line[i] != '\n')
		game->f_text[y++] = line[i++];
	game->f_text[y] = '\0';
	game->nbr_text[4]++;
}

/**
 * @brief Récupère et stocke la couleur du plafond (C)
 *
 * @param game
 * @param line
 * @param i
 */
void	grab_c_text(t_game *game, char *line, int i)
{
	int	y;

	y = 0;
	if (game->nbr_text[5] != 0)
		return ;
	while (line && line[i] == 32)
		i++;
	game->c_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && line[i] != '\n')
		game->c_text[y++] = line[i++];
	game->c_text[y] = '\0';
	game->nbr_text[5]++;
}

void	load_textures(t_game *game)
{
	int	width;
	int	height;

	game->textures->tex_no_img = mlx_xpm_file_to_image(game->mlx, game->no_text,
			&width, &height);
	if (!game->textures->tex_no_img)
		ft_error(game, "Failed to load North texture");
	game->textures->tex_no_data = mlx_get_data_addr(game->textures->tex_no_img,
			&game->textures->tex_bpp, &game->textures->tex_line_len,
			&game->textures->tex_endian);
	game->textures->tex_so_img = mlx_xpm_file_to_image(game->mlx, game->so_text,
			&width, &height);
	if (!game->textures->tex_so_img)
		ft_error(game, "Failed to load South texture");
	game->textures->tex_so_data = mlx_get_data_addr(game->textures->tex_so_img,
			&game->textures->tex_bpp, &game->textures->tex_line_len,
			&game->textures->tex_endian);
	game->textures->tex_ea_img = mlx_xpm_file_to_image(game->mlx, game->ea_text,
			&width, &height);
	if (!game->textures->tex_ea_img)
		ft_error(game, "Failed to load East texture");
	game->textures->tex_ea_data = mlx_get_data_addr(game->textures->tex_ea_img,
			&game->textures->tex_bpp, &game->textures->tex_line_len,
			&game->textures->tex_endian);
	game->textures->tex_we_img = mlx_xpm_file_to_image(game->mlx, game->we_text,
			&width, &height);
	if (!game->textures->tex_we_img)
		ft_error(game, "Failed to load West texture");
	game->textures->tex_we_data = mlx_get_data_addr(game->textures->tex_we_img,
			&game->textures->tex_bpp, &game->textures->tex_line_len,
			&game->textures->tex_endian);
	game->textures->tex_width = width;
	game->textures->tex_height = height;
}
