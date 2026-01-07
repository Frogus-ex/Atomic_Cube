/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frogus <frogus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:56:24 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/07 13:55:49 by frogus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// toutes les fonction ft_error devrons contenir un free game ulterieurement

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
