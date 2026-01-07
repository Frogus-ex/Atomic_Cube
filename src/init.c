/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frogus <frogus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:25:04 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/07 11:50:21 by frogus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	game_init(t_game **game)
{
	*game = ft_calloc(1, sizeof(t_game));
	if (!*game)
	{
		ft_error(NULL, "game allocation failed");
		return ;
	}
	
	(*game)->mlx = NULL;
	(*game)->win = NULL;
	(*game)->nbr_text = ft_calloc(6, sizeof(int));
	if (!(*game)->nbr_text)
	{
		ft_error(*game, "nbr_text allocation failed");
		return ;
	}
	(*game)->nbr_line = 0;
}
