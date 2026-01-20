/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:40:17 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/20 16:02:17 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	free_struct(t_game *game)
{
	if (!game)
		return ;
	if (game->no_text)
		free(game->no_text);
	if (game->so_text)
		free(game->so_text);
	if (game->we_text)
		free(game->we_text);
	if (game->ea_text)
		free(game->ea_text);
	if (game->f_text)
		free(game->f_text);
	if (game->c_text)
		free(game->c_text);
	if (game->nbr_text)
		free(game->nbr_text);
	if (game->player)
		free(game->player);
}

void	free_all(t_game *game)
{
	if (!game)
		return ;
	free_struct(game);
	if (game->img)
	{
		if (game->img->img && game->mlx)
			mlx_destroy_image(game->mlx, game->img->img);
		free(game->img);
	}
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->fd >= 0)
		close(game->fd);
	free(game);
}

void	ft_error(t_game *game, char *s)
{
	printf("%s\n", s);
	free_all(game);
}

int	ft_gnlen(char *gnl)
{
	int	i;

	i = 0;
	while (gnl[i] && gnl[i] != '\n')
	{
		i++;
	}
	return (i);
}
