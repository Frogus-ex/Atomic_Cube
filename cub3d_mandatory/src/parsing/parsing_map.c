/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:20:20 by aautret           #+#    #+#             */
/*   Updated: 2026/02/03 11:16:30 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * @brief
 * - Trouver la position du premier '1'
 * - Checker que le dernier element est un '1'
 * - Si aucun '1' trouvé, retourner erreur
 *
 * - Boucler a partir de first_one
 *      - Vérifier que chaque caractère est valide (1, 0, N, S, E, W ou espace)
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
		if (!ft_strchr("10NSEW \n", line[i]))
			return (ft_error(NULL, "invalid caracter detected"), 1);
		if (ft_strchr("NSEW", line[i]) && game->flag_players == 1)
			return (ft_error(NULL, "invalid number of player in map"), 1);
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
