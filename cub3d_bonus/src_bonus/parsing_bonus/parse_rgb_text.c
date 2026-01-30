/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:42:18 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/30 11:12:55 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

static int	parse_all_color(t_game *game)
{
	int	i;

	i = 0;
	while (game->c_text[i])
	{
		if ((game->c_text[i] >= '0' && game->c_text[i] <= '9')
			|| game->c_text[i] == ',' || game->c_text[i] == 32
			|| (game->c_text[i] >= 9 && game->c_text[i] <= 12))
			i++;
		else
			return (0);
	}
	i = 0;
	while (game->f_text[i])
	{
		if ((game->f_text[i] >= '0' && game->f_text[i] <= '9')
			|| game->f_text[i] == ',' || game->f_text[i] == 32
			|| (game->f_text[i] >= 9 && game->f_text[i] <= 12))
			i++;
		else
			return (0);
	}
	return (1);
}

static int	parse_c_rgb(t_game *game)
{
	int (i) = 0;
	int (y) = 0;
	game->c_rgb = malloc(sizeof(int) * 3);
	while (game->c_text[i])
	{
		if (game->c_text[i] == ',' || game->c_text[i] == 32
			|| (game->c_text[i] >= 9 && game->c_text[i] <= 12))
			i++;
		else if (game->c_text[i] >= '0' && game->c_text[i] <= '9')
		{
			game->c_rgb[y] = ft_atoi(&game->c_text[i]);
			y++;
			if (y > 3)
				return (0);
			while (game->c_text[i] >= '0' && game->c_text[i] <= '9')
				i++;
		}
		else
			i++;
	}
	if (y < 3)
		return (0);
	return (1);
}

static int	parse_f_rgb(t_game *game)
{
	int (i) = 0;
	int (y) = 0;
	game->f_rgb = malloc(sizeof(int) * 3);
	while (game->f_text[i])
	{
		if (game->f_text[i] == ',' || game->f_text[i] == 32
			|| (game->f_text[i] >= 9 && game->f_text[i] <= 12))
			i++;
		else if (game->f_text[i] >= '0' && game->f_text[i] <= '9')
		{
			game->f_rgb[y] = ft_atoi(&game->f_text[i]);
			y++;
			if (y > 3)
				return (0);
			while (game->f_text[i] >= '0' && game->f_text[i] <= '9')
				i++;
		}
		else
			i++;
	}
	if (y < 3)
		return (0);
	return (1);
}

static int	rgb_checker(t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (game->c_rgb[i] > 255 || game->c_rgb[i] < 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (game->f_rgb[i] > 255 || game->f_rgb[i] < 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_colors_param(t_game *game)
{
	if (!parse_all_color(game))
		return (0);
	else if (!parse_c_rgb(game))
		return (0);
	else if (!parse_f_rgb(game))
		return (0);
	else if (!rgb_checker(game))
		return (0);
	else
		return (1);
}
