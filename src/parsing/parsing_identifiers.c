/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 08:16:38 by aautret           #+#    #+#             */
/*   Updated: 2026/01/07 15:56:23 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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

int	parse_identifier_line(t_game *game, char *line)
{
	(void)game;
	(void)line;
	printf("PARSING DE TOM\n");
	return (0);
}
