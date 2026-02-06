/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:37:30 by frogus            #+#    #+#             */
/*   Updated: 2026/02/06 13:44:42 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

static void	grab_no_text(t_game *game, char *line, int i)
{
	int	y;

	y = 0;
	if (game->nbr_text[0] != 0)
		return (ft_error(NULL, "too many north textures"));
	while (line && line[i] == 32)
		i++;
	game->no_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && line[i] != '\n' && line[i] != '\r')
		game->no_text[y++] = line[i++];
	while (y > 0 && (game->no_text[y - 1] == 32 || game->no_text[y
				- 1] == '\t'))
		y--;
	game->no_text[y] = '\0';
	game->nbr_text[0]++;
}

static void	grab_so_text(t_game *game, char *line, int i)
{
	int	y;

	y = 0;
	if (game->nbr_text[1] != 0)
		return (ft_error(NULL, "too many south textures"));
	while (line && line[i] == 32)
		i++;
	game->so_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && line[i] != '\n' && line[i] != '\r')
		game->so_text[y++] = line[i++];
	while (y > 0 && (game->so_text[y - 1] == 32 || game->so_text[y
				- 1] == '\t'))
		y--;
	game->so_text[y] = '\0';
	game->nbr_text[1]++;
}

int	check_id(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == 32)
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		grab_no_text(game, line, i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		grab_so_text(game, line, i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		grab_we_text(game, line, i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		grab_ea_text(game, line, i + 2);
	else if (line[i] == 'F' && line[i + 1] == 32)
		grab_f_text(game, line, i + 1);
	else if (line[i] == 'C' && line[i + 1] == 32)
		grab_c_text(game, line, i + 1);
	else if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A'
			&& line[i] <= 'Z'))
		return (0);
	return (1);
}

int	parse_identifiers_line(t_game *game, char *line)
{
	if (!check_id(game, line))
		return (0);
	return (1);
}
