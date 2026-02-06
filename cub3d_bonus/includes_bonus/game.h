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

#ifndef GAME_H
# define GAME_H

# include "cub3D.h"

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
	void				*tex_door_img;
	char				*tex_no_data;
	char				*tex_so_data;
	char				*tex_ea_data;
	char				*tex_we_data;
	char				*tex_door_data;
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

typedef struct s_ray_params
{
	double				ray_hit_x;
	double				ray_hit_y;
	double				step_x;
	double				step_y;
	int					map_x;
	int					map_y;
	int					found_wall;
	int					is_door;
	double				distance;
	int					is_horizontal;
}						t_ray_params;

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
	double				z_buffer[SCREEN_WIDTH];
	double				corrected_wall_distance;
	double				distance_x;
	double				distance_y;
	double				wall_distance;
	double				wall_size;
	double				wall_start;
	double				wall_end;
	double				ray_dir_x;
	double				ray_dir_y;
	double				nx;
	double				ny;
	int					tx;
	int					ty;
	t_game				*game;
	t_map				*map;
	t_player			*player;
	t_texture			*texture;
	t_ray_params		*ray_params;
}						t_img;

/************************************************************************
 *									GAME								*
 ***********************************************************************/
// draw_game.c
void					draw_wall(t_game *game, int x, double wall_size,
							double angle);
void					put_cub3d_to_wnd(t_img *img);
void					render_frame(t_img *img);

// game_loop.c
void					simple_mooves(t_game *game, t_img *img);
int						game_loop(t_game *game);

// game_utils.c
void					my_put_pixel(t_img *img, int x, int y, int color);
int						cross_close(t_game *game);
int						find_biggest(t_img *img);

// manage_moves_utils.c
int						key_press(int keycode, t_game *game);
int						key_released(int keycode, t_game *game);
int						collision_checker(t_img *img);

// manage_moves.c
void					moving_pix_by_pix(t_img *img, double dx, double dy);
double					calc_dx(t_img *img, int keycode);
double					calc_dy(t_img *img, int keycode);
void					update_all_sprites(t_game *game, int delta_ms);

// manage_textures.c
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

// doors.c
void					open_door(t_game *game);

#endif