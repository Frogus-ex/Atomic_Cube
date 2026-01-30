/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:40:17 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/30 11:13:18 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D.h"

void	ft_error(t_game *game, char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
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
