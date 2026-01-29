/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:44:23 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/29 17:05:58 by aautret          ###   ########.fr       */
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
		return (ft_error(NULL, "too many west textures"));
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
		return (ft_error(NULL, "too many east textures"));
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
		return (ft_error(NULL, "too many floor textures"));
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
		return (ft_error(NULL, "too many ceilling textures"));
	while (line && line[i] == 32)
		i++;
	game->c_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && line[i] != '\n')
		game->c_text[y++] = line[i++];
	game->c_text[y] = '\0';
	game->nbr_text[5]++;
}

int	load_single_texture(t_game *game, char *path, void **img,
		char **data)
{
	int	w;
	int	h;

	*img = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
	if (!(*img))
		return (ft_error(game, "Failed to load texture"), 1);
	*data = mlx_get_data_addr(*img, &game->textures->tex_bpp,
			&game->textures->tex_line_len, &game->textures->tex_endian);
	game->textures->tex_width = w;
	game->textures->tex_height = h;
	return (0);
}
