/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:25:04 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/06 13:51:13 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	count_file_lines(t_game *game, char *av)
{
	char	*stash;
	char	*line;

	stash = NULL;
	game->fd = open(av, O_RDONLY);
	if (game->fd < 0)
		return (ft_error("file doesn t exist"), 1);
	line = get_next_line(game->fd, &stash);
	if (!line)
		return (free(line), free(stash), close(game->fd), 1);
	while (line)
	{
		free(line);
		line = get_next_line(game->fd, &stash);
		game->nbr_line++;
	}
	return (game->nbr_line);
}

void	game_init(t_game **game, char *av)
{
	*game = ft_calloc(1, sizeof(t_game));
	if (!*game)
	{
		ft_error("game allocation failed");
		return ;
	}
	(*game)->file_lines = ft_calloc(count_file_lines(*game, av),
			sizeof(char *));
	if (!(*game)->file_lines)
	{
		ft_error("file_lines allocation failed");
		free(*game);
		*game = NULL;
		return ;
	}
	(*game)->mlx = NULL;
	(*game)->win = NULL;
	(*game)->nbr_line = 0;
}
