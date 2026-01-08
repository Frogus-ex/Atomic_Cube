/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:20:20 by aautret           #+#    #+#             */
/*   Updated: 2026/01/08 15:28:30 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

/**
 * @brief Trouve la position du premier 1
 * 
 * - Rajouter une protection pour que seuls des espaces avant le '1' soient
 * valides
 * 
 * @param line 
 * @return int 
 */
static int	get_first_one(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1')
			return (i);
		i++;
	}
	return (1);
}

/**
 * @brief Verifie que le dernier element de la ligne est un '1'
 * 
 * @param line 
 * @return int
 * 
 * - 1 = ECHEC (le dernier element n'est pas un '1')
 * 
 * - 0 = SUCCES
 */
static int	check_last_one(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (line[i - 2] != '1')
		return (1);
	else
		return (0);
}

static int	check_first_one(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != '1')
		return (1);
	return (0);
}

/**
 * @brief Chercher le dernier caractère different d'un ' ' avant celui ci
 *
 * Verifie que c'est un 1
 * @param line 
 * @param i 
 * @param first_one 
 * @return int 
 * 
 * - 1 = ECHEC (pas d'encadrement avec un 1)
 * 
 * - 0 = SUCCES (encadrement du debut valide)
 */
// static int	check_before(char *line, int i, int first_one)
// {
// 	int	x;

// 	x = 1;
// 	while (line[i - x] == ' ' && x > first_one)
// 	{
// 		x--;
// 	}
// 	if (line[x] != '1')
// 		return (1);
// 	return (0);
// }

// static int	check_after(char *line, int i)
// {
// 	int	x;

// 	x = 1;
// 	while (line[i + x] && line[i + x] == ' ')
// 	{
// 		x++;
// 	}
// 	if (line[x] != '1')
// 		return (1);
// 	return (0);
// }

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
int	parse_map_line(char *line)
{
	int		first_one;
	int		i;

	if (check_first_one(line) == 1)
		return (printf("error : delimitation of map\n"), 1);
	if (check_last_one(line) == 1)
	{
		printf("line = %s\n", line);
		return (printf("error: last invalid map\n"), 1);
	}
	first_one = get_first_one(line);
	i = first_one;
	while (line[i])
	{
		if (!ft_strchr("10NSEW \n", line[i]))
			return (printf("error: invalid caracter detected\n"), 1);
		// if (line[i] == ' ')
		// {
		// 	if (check_before(line, i, first_one) && check_after(line, i))
		// 		return (printf("error: invalid framework\n"), 1);
		// }
		i++;
	}
	return (0);
}
