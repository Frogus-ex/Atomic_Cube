/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:13:10 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/06 14:24:06 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "GNL/get_next_line.h"
# include "libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <stdio.h>
# include <time.h>
# include <unistd.h>

# define IMG_PXL 50
# define TILE_SIZE 50
# define WND_NAME "Atomic_Cube"

typedef struct s_player
{
	int			y;
	int			x;
}				t_player;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			screen_width;
	int			screen_height;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			endian;
	int			line_length;
}				t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		*file_line;
	char		*clean_file_line;
	int			nbr_line;
	int			fd;
	t_player	*player;
	t_img		*img;
}				t_game;

int				ft_gnlen(char *gnl);
void			ft_error(char *s);
void			check_arg_param(int ac, char **av);
int				check_cub_file(t_game *game, char *av);
void			check_identifier(char *line);
void			game_init(t_game **game);
void			clean_identifier_line(t_game *game, char *line);

// parsing_map.c
int				check_valid_map(char *line);

#endif