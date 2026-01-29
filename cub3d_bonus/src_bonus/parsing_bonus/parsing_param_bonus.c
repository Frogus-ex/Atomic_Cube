/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:56:24 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/29 11:43:22 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	check_arg_param(int ac, char **av)
{
	int		len;
	char	*name;

	if (ac != 2)
		ft_error(NULL, "wrong number of args");
	name = av[1];
	len = ft_strlen(name);
	if (len < 5 || ft_strncmp(name + len - 4, ".cub", 4) != 0)
		ft_error(NULL, "file extention must be .cub");
	if (ft_strnstr(name, ".cub", len - 4))
		ft_error(NULL, "file extention must be .cub");
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
