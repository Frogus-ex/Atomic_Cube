/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:56:24 by tlorette          #+#    #+#             */
/*   Updated: 2025/12/17 17:55:55 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// toutes les fonction ft_error devrons contenir un free game ulterieurement

void	check_arg_param(int ac, char **av, t_game *game)
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

void	check_cub_file(t_game *game, char *av)
{
	char	*stash;

	stash = NULL;
	game->fd = open(av, O_RDONLY);
	if (game->fd < 0)
		return (ft_error("file doesn t exist"), 1);
	game->nbr_line = 0;
	game->file_line = get_next_line(av, &stash);
	if (!game->file_line)
		return (free(game->file_line), close(game->fd), 1);
	while (game->file_line)
	{
		check_line(game->file_line);
		game->nbr_line = ft_gnlen(game->file_line);
		game->nbr_line++;
	}
	return (close(game->fd), 0);
}

void	check_line(char *line)
{
	int		i;
	int		y;
	char	*identifier;
	char	*value;

	
}
