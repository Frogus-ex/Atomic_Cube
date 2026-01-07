/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frogus <frogus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:13:10 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/07 13:54:59 by frogus           ###   ########.fr       */
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
	char		*no_text;
	char		*so_text;
	char		*we_text;
	char		*ea_text;
	char		*f_text;
	char		*c_text;
	int			*nbr_text;
	int			nbr_line;
	int			fd;
	t_player	*player;
	t_img		*img;
}				t_game;

int				ft_gnlen(char *gnl);
void			ft_error(t_game *game, char *s);
void			free_all(t_game *game);
void			check_arg_param(int ac, char **av);
void			game_init(t_game **game);
int				parse_identifer_line(t_game *game, char *av);
int				count_space(char *line);
int				count_lines(char **lines);
int				parse_identifer_line(t_game *game, char *av);
int				check_identifier(char *line);
void			check_id(t_game *game, char *line);
void			grab_we_text(t_game *game, char *line, int i);
void			grab_ea_text(t_game *game, char *line, int i);
void			grab_c_text(t_game *game, char *line, int i);
void			grab_f_text(t_game *game, char *line, int i);



#endif