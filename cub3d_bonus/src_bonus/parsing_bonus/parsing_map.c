/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: autret <autret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:20:20 by aautret           #+#    #+#             */
/*   Updated: 2026/02/05 15:50:15 by autret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D.h"

/**
 * @brief
 * - Trouver la position du premier '1'
 * - Checker que le dernier element est un '1'
 * - Si aucun '1' trouvé, retourner erreur
 *
 * - Boucler a partir de first_one
 *      - Vérifier que chaque caractère est valide
 *        (1, 0, N, S, E, W, D, A ou espace)
 *      - Si c'est un espace :
 *           - Check encadrement avant
 *           - Chercher le prochain caractère non-espace APRÈS cet espace
 *           - Vérifier que c'est un '1'
 *           - Si l'un des deux n'est pas '1', retourner erreur
 * @param line
 * @return int
 */
int	parse_map_line(t_game *game, char *line)
{
	int (i) = 0;
	while (line[i])
	{
		if (!ft_strchr("10NSEWDA \n", line[i]))
			return (printf("error: invalid caracter detected \n"), 1);
		if (ft_strchr("NSEW", line[i]) && game->flag_players == 1)
			return (printf("error: invalid number of players in map\n"), 1);
		else if (ft_strchr("NSEW", line[i]) && game->flag_players == 0)
		{
			game->flag_players = 1;
			if (line[i] == 'N')
				game->player->direction_vue = M_PI_2;
			else if (line[i] == 'W')
				game->player->direction_vue = M_PI;
			else if (line[i] == 'S')
				game->player->direction_vue = -M_PI_2;
			else if (line[i] == 'E')
				game->player->direction_vue = 0;
		}
		i++;
	}
	return (0);
}
