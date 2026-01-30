/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:56:24 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/30 11:13:05 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

int	check_arg_param(char **av)
{
	int		len;
	char	*name;

	name = av[1];
	len = ft_strlen(name);
	if (len < 5 || ft_strncmp(name + len - 4, ".cub", 4) != 0)
		return (ft_error(NULL, "file extention must be .cub"), 0);
	if (ft_strnstr(name, ".cub", len - 4))
		return (ft_error(NULL, "file extention must be .cub"), 0);
	return (1);
}

int	check_cub_file(t_game *game, char *av)
{
	char	*stash;
	char	*line;

	stash = NULL;
	game->fd = open(av, O_RDONLY);
	if (game->fd < 0)
		return (ft_error(NULL, "file doesn t exist"), 1);
	game->nbr_line = 0;
	line = get_next_line(game->fd, &stash);
	if (!line)
		return (free(line), close(game->fd), 1);
	while (line)
	{
		game->nbr_line = ft_gnlen(line);
		free(line);
		line = get_next_line(game->fd, &stash);
	}
	free(stash);
	return (close(game->fd), 0);
}
