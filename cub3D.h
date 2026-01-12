/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:13:10 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/12 18:00:53 by tlorette         ###   ########.fr       */
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

typedef enum e_parse_state
{
	PARSES_IDENTIFIERS,
	PARSE_MAP
}				t_parse_state;

typedef struct s_player
{
	int			y;
	int			x;
}				t_player;

typedef struct s_map
{
	char		**map;
	int			y;
	int			x;
	int			width;
	int			height;
	int			total_size;
}				t_map;

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
// void			clean_identifier_line(t_game *game, char *line);
void			ft_error(t_game *game, char *s);
void			free_all(t_game *game);
// int				check_arg_param(int ac, char **av);
void			game_init(t_game **game);
void			map_init(t_map **map);
int				parse_identifiers_line(t_game *game, char *line);
int				count_space(char *line);
int				count_file_lines(t_game *game, char *av);
int				check_identifier(char *line);
int				count_lines(char **lines);

/************************************************************************
 *									SRC									*
 ***********************************************************************/
// cleaner.c
int				count_file_lines(t_game *game, char *av);
// init.c

// utils.c
int				ft_gnlen(char *gnl);

/************************************************************************
 *								PARSING									*
 ***********************************************************************/
// parsing.c
int				parsing(t_game *game, char *av);

// parsing_identifiers.c

// parsing_map.c
int				parse_map_line(char *line);
int				detector_start_map(char *line);
int				check_id(t_game *game, char *line);
void			grab_we_text(t_game *game, char *line, int i);
void			grab_ea_text(t_game *game, char *line, int i);
void			grab_c_text(t_game *game, char *line, int i);
void			grab_f_text(t_game *game, char *line, int i);
int				count_map_lines(t_game *game, t_map *map, char *av);
void			map_copy(t_map *map, char *av);
int				get_map_width(char *line);
void			read_from_map(t_game *game, t_map *map, char *av);
int				get_greater_width(char *av);
int				get_map_height(char *av);
void			map_alloc(t_map *map, char *av);

#endif