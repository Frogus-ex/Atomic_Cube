/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:07:26 by tlorette          #+#    #+#             */
/*   Updated: 2026/01/28 13:34:19 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H_BONUS
# define GAME_H_BONUS

# include "cub3D_bonus.h"

typedef struct s_game	t_game;
typedef struct s_map	t_map;
typedef struct s_player	t_player;

typedef struct s_texture
{
	void				*text;
	void				*tex_no_img;
	void				*tex_so_img;
	void				*tex_ea_img;
	void				*tex_we_img;
	char				*tex_no_data;
	char				*tex_so_data;
	char				*tex_ea_data;
	char				*tex_we_data;
	int					tex_width;
	int					tex_height;
	int					tex_bpp;
	int					tex_line_len;
	int					tex_endian;
	int					tex_x;
	int					tex_y;
	int					side;
	double				wall_x;
}						t_texture;

typedef struct s_img
{
	void				*img;
	char				*addr;
	int					screen_width;
	int					screen_height;
	int					width;
	int					height;
	int					bits_per_pixel;
	int					endian;
	int					line_length;
	double				distance_x;
	double				distance_y;
	double				wall_distance;
	double				wall_size;
	double				wall_start;
	double				wall_end;
	double				ray_dir_x;
	double				ray_dir_y;
	t_game				*game;
	t_map				*map;
	t_player			*player;
	t_texture			*texture;
}						t_img;

typedef struct s_ray_params
{
	double				ray_hit_x;
	double				ray_hit_y;
	double				step_x;
	double				step_y;
	int					map_x;
	int					map_y;
	int					found_wall;
	double				distance;
	int					is_horizontal;
}						t_ray_params;

/************************************************************************
 *									GAME								*
 ***********************************************************************/
// draw_game.c
void					put_cub3d_to_wnd(t_img *img);

// game_utils.c
void					my_put_pixel(t_img *img, int x, int y, int color);
int						cross_close(t_game *game);
int						find_biggest(t_img *img);

// init_vison.c
void					get_distance(t_img *img, double xm, double ym,
							double angle);

// key_handle.c
int						player_input(t_game *game);
void					player_moves(t_img *img, int new_y, int new_x);

// key_handle_utils.c
int						key_press(int keycode, t_game *game);
int						key_released(int keycode, t_game *game);

// draw_cub3d.c
void					draw_wall(t_img *img, int x, double wall_size,
							double angle);
int						load_textures(t_game *game);
void					draw_wall_text(t_img *img, int x, int y, double angle);

// raycaster_utils.c
double					norme_angle(double ray_angle);
void					setup_horizontal_ray(t_img *img, double ray_angle,
							t_ray_params *params);
void					setup_vertical_ray(t_img *img, double ray_angle,
							t_ray_params *params);
double					cast_ray(t_img *img, t_ray_params *params);

// raycaster.c
void					set_wall_dir(t_texture *texture, double ray_angle,
							int is_horiz);
void					get_wall_hit_dda(t_img *img, t_ray_params *params,
							double ray_angle);
void					get_distance_dda(t_img *img, t_ray_params *params,
							double ray_angle);
void					cast_ray_dda(t_img *img, double ray_angle, int column);

#endif