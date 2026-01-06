/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:56:24 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/06 14:43:52 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// toutes les fonction ft_error devrons contenir un free game ulterieurement

void	check_arg_param(int ac, char **av)
{
	int		len;
	char	*name;

	if (ac != 2)
		ft_error("wrong number of args");
	name = av[1];
	len = ft_strlen(name);
	if (len < 5 || ft_strncmp(name + len - 4, ".cub", 4) != 0)
		ft_error("file extention must be .cub");
	if (ft_strnstr(name, ".cub", len - 4))
		ft_error("file extention must be .cub");
}

int	check_cub_file(t_game *game, char *av)
{
	char	*stash;
	char	*line;
	int		size;

	stash = NULL;
	game->fd = open(av, O_RDONLY);
	if (game->fd < 0)
		return (ft_error("file doesn t exist"), 1);
	line = get_next_line(game->fd, &stash);
	if (!line)
		return (free(line), free(stash), close(game->fd), 1);
	while (line && game->nbr_line < 1000)
	{
		size = ft_strlen(line) - count_space(line) + 1;
		game->file_lines[game->nbr_line] = malloc(sizeof(char) * size);
		if (!game->file_lines[game->nbr_line])
			return (free(line), free(stash), close(game->fd), 1);
		clean_identifier_line(game, line);
		free(line);
		line = get_next_line(game->fd, &stash);
		game->nbr_line++;
	}
	free(stash);
	return (close(game->fd), 0);
}

void	clean_identifier_line(t_game *game, char *line)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (line[i] == 32)
		i++;
	while (line[i])
	{
		if (line[i] != 32)
			game->file_lines[game->nbr_line][y++] = line[i];
		if ((line[i] >= 'A' && line[i] <= 'Z') && line[i + 1] == 32)
			game->file_lines[game->nbr_line][y++] = 32;
		i++;
	}
	game->file_lines[game->nbr_line][y] = '\0';
	printf("%s", game->file_lines[game->nbr_line]);
}

int	count_space(char *line)
{
	int	i;
	int	space;

	i = -1;
	space = 0;
	while (line[++i])
	{
		if (line[i] == 32)
			space++;
	}
	return (space);
}

int	check_identifier(char *line)
{
	if (ft_strcmp("NO", line) == 0)
		return (1);
	if (ft_strcmp("SO", line) == 0)
		return (1);
	if (ft_strcmp("WE", line) == 0)
		return (1);
	if (ft_strcmp("EA", line) == 0)
		return (1);
	if (ft_strcmp("C", line) == 0)
		return (1);
	if (ft_strcmp("F", line) == 0)
		return (1);
	return (0);
}
