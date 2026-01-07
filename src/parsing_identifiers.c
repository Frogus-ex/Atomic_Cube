/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frogus <frogus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:37:30 by frogus            #+#    #+#             */
/*   Updated: 2026/01/07 16:32:57 by frogus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	grab_no_text(t_game *game, char *line, int i)
{
	int	y;

	y = 0;
	while (line && line[i] == 32)
		i++;
	if (game->nbr_text[0] == 0)
		game->no_text = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i] && line[i] != '\n' && game->nbr_text[0] == 0)
		game->no_text[y++] = line[i++];
	game->no_text[y] = 0;
	game->nbr_text[0]++;
}

static void	grab_so_text(t_game *game, char *line, int i)
{
	int	y;

	y = 0;
	while (line && line[i] == 32)
		i++;
	if (game->nbr_text[1] == 0)
		game->so_text = malloc(sizeof(char) * (ft_strlen(line) - i)+ 1);
	while (line[i] && line[i] != '\n' && game->nbr_text[1] == 0)
		game->so_text[y++] = line[i++];
	game->so_text[y] = 0;
	game->nbr_text[1]++;
}

static int	count_text(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6 && game->nbr_text[i] == 1)
		i++;
	if (i == 6)
		return (1);
	else
		return (0);
}

int	check_id(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line && line[i] == 32)
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
	else if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z'))
		return (0);
	return (1);
}

int	parse_identifer_line(t_game *game, char *av)
{
	char	*stash;
	char	*line;

	stash = NULL;
	game->fd = open(av, O_RDONLY);
	if (game->fd < 0)
		return (ft_error(game, "file doesn t exist"), 0);
	line = get_next_line(game->fd, &stash);
	if (!line)
		return (free(line), free(stash), close(game->fd), 0);
	while (line)
	{
		game->nbr_line++;
		if (!check_id(game, line))
			return (ft_error(game, "wrong identifier"), free(line), free(stash), 0);
		free(line);
		line = get_next_line(game->fd, &stash);
	}
	if (count_text(game) == 0)
		return (ft_error(NULL, "wrong number of textures"), 0);
	return (1);
}
