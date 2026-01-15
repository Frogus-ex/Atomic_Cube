/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_id.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:01:18 by frogus            #+#    #+#             */
/*   Updated: 2026/01/15 17:50:13 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	while (line && line[i] == 32)
		i++;
	if (game->nbr_text[2] == 0)
		game->we_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && line[i] != '\n' && game->nbr_text[2] == 0)
		game->we_text[y++] = line[i++];
	game->we_text[y] = 0;
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
	while (line && line[i] == 32)
		i++;
	if (game->nbr_text[3] == 0)
		game->ea_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && line[i] != '\n' && game->nbr_text[3] == 0)
		game->ea_text[y++] = line[i++];
	game->ea_text[y] = 0;
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
	while (line && line[i] == 32)
		i++;
	if (game->nbr_text[4] == 0)
		game->f_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && line[i] != '\n' && game->nbr_text[4] == 0)
		game->f_text[y++] = line[i++];
	game->f_text[y] = 0;
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
	while (line && line[i] == 32)
		i++;
	game->c_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && line[i] != '\n' && game->nbr_text[5] == 0)
		game->c_text[y++] = line[i++];
	game->c_text[y] = 0;
	game->nbr_text[5]++;
}
