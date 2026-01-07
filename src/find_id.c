/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_id.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frogus <frogus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:01:18 by frogus            #+#    #+#             */
/*   Updated: 2026/01/07 12:02:06 by frogus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	grab_we_text(t_game *game, char *line, int i)
{
	int	y;

	y = 0;
	while (line && line[i] == 32)
		i++;
	game->we_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && game->nbr_text[2] == 0)
		game->we_text[y++] = line[i++];
	game->we_text[y] = 0;
	game->nbr_text[2]++;
}

void	grab_ea_text(t_game *game, char *line, int i)
{
	int	y;

	y = 0;
	while (line && line[i] == 32)
		i++;
	game->ea_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && game->nbr_text[3] == 0)
		game->ea_text[y++] = line[i++];
	game->ea_text[y] = 0;
	game->nbr_text[3]++;
}

void	grab_f_text(t_game *game, char *line, int i)
{
	int	y;

	y = 0;
	while (line && line[i] == 32)
		i++;
	game->f_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && game->nbr_text[4] == 0)
		game->f_text[y++] = line[i++];
	game->f_text[y] = 0;
	game->nbr_text[4]++;
}

void	grab_c_text(t_game *game, char *line, int i)
{
	int	y;

	y = 0;
	while (line && line[i] == 32)
		i++;
	game->c_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && game->nbr_text[5] == 0)
		game->c_text[y++] = line[i++];
	game->c_text[y] = 0;
	game->nbr_text[5]++;
}
