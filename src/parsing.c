/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:56:24 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/06 14:25:25 by aautret          ###   ########.fr       */
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

	stash = NULL;
	game->fd = open(av, O_RDONLY);
	if (game->fd < 0)
		return (ft_error("file doesn t exist"), 1);
	game->nbr_line = 0;
	line = get_next_line(game->fd, &stash);
	if (!line)
		return (free(line), close(game->fd), 1);
	while (line)
	{
		//PARSER
		// check_identifier(game->file_line);
		check_valid_map(line);
		game->nbr_line = ft_gnlen(line);
		free(line);
		line = get_next_line(game->fd, &stash);
	}
	free(stash);
	return (close(game->fd), 0);
}

