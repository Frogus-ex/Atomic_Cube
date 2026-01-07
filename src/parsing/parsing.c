/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:56:24 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/07 16:26:05 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

// toutes les fonction ft_error devrons contenir un free game ulterieurement

/**
 * @brief Detecte si une ligne marque le debut de la section map
 *
 * Ignore les espaces, puis examine le premier caractere :
 *
 * 	- '1' => debut de map
 *
 * 	- fin de ligne => map une map (ligne vide / esapces)
 *
 * 	- '0' ou 'NSEW' => contenu invalide de debut de map
 * @param line
 * @return int
 */
static int	detector_start_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	if (line[i] == '1')
		return (1);
	return (0);
}

/**
 * @brief Route une ligne vers le bon parser en fonction de l'etat, et bascule
 * en mode map des la premiere ligne valide de la map
 *
 *En état PARSE_IDENTIFIERS:

 * - (-1) (depuis is_map_start_line) => erreur "invalid line before map start"

 * - 1 => passe l’état à PARSE_MAP et appelle store_map_line()

 * - 0 => traite la ligne comme identifiant via store_identifier_line()
 *
 * En état PARSE_MAP:
 *
 * - Toujours store_map_line() (les lignes vides déclenchent une erreur de
 * contiguïté)
 * @param game
 * @param line
 * @param state
 * @return int 0 == SUCCESS / 1 == FAILURE
 */
static int	detector_and_store_line(t_game *game, char *line,
		t_parse_state *state)
{
	int	detect;

	detect = detector_start_map(line);
	if (*state == PARSES_IDENTIFIERS)
	{
		if (detect == -1)
			return (ft_error("error: invalid line before map start"), 1);
		if (detect == 1)
		{
			*state = PARSE_MAP;
			return (parse_map_line(line));
		}
		return (parse_identifier_line(game, line));
	}
	return (parse_map_line(line));
}

int	parsing(t_game *game, char *av)
{
	char			*stash;
	char			*line;
	int				status;
	t_parse_state	state;

	stash = NULL;
	status = 0;
	state = PARSES_IDENTIFIERS;
	game->fd = open(av, O_RDONLY);
	if (game->fd < 0)
		return (ft_error("file doesnt exist"), 1);
	line = get_next_line(game->fd, &stash);
	if (!line)
		return (free(line), free(stash), close(game->fd), 1);
	while (line && game->nbr_line < 1000 && status == 0)
	{
		status = detector_and_store_line(game, line, &state);
		if (status == 1)
			return (free(line), 1);
		free(line);
		line = get_next_line(game->fd, &stash);
	}
	free(line);
	free(stash);
	return (close(game->fd), status);
}
