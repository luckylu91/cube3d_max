/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:28:40 by lzins             #+#    #+#             */
/*   Updated: 2021/02/20 11:12:30 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"
#include <math.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include "linux.h"

#define OUTSIDE ' '
#define EMPTY '0'
#define WALL '1'
#define GHOST '2'
#define PEA '.'
#define PLAYER_N 'N'
#define PLAYER_S 'S'
#define PLAYER_W 'W'
#define PLAYER_E 'E'
#define TELEP 'T'
#define MAP_CHARS " 012NSEWT"
#define ENEMIES "2"
#define SPRITES ".2"
//linux
#define KEY_ESC 65307
#define KEY_W 122
#define KEY_A 113
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
// OSX
// #define KEY_ESC 53
// #define KEY_W 13
// #define KEY_A 0
// #define KEY_S 1
// #define KEY_D 2
// #define KEY_LEFT 123
// #define KEY_RIGHT 124
#define NO_KEY -1
#define KEYMASK_W (1 << 0)
#define KEYMASK_A (1 << 1)
#define KEYMASK_S (1 << 2)
#define KEYMASK_D (1 << 3)
#define KEYMASK_LEFT (1 << 4)
#define KEYMASK_RIGHT (1 << 5)
#define NORTH 0
#define SOUTH 1
#define WEST 2
#define EAST 3
#define FLOOR 4
#define CEIL 5
#define SCREEN_DIST .5
#define SCREEN_WIDTH_SIZE 1.
#define WALL_SIZE 1.
#define COLLISION_RADIUS .3
#define EPSILON .01
#define ENEMY_SPEED 2.5
#define PLAYER_SPEED 4.
#define TIME_INVUL 1.
#define TIME_RESTART 1.
#define TIME_BEEP_LIFE .2
#define MINI_SIZE .15
#define MINI_OX .1
#define MINI_OY .1
#define MINI_THICKNESS .2

typedef struct  s_img
{
	void		*img;
	char		*data;
	int			bpp;
	int			lsize;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_pt2d
{
	double		x;
	double		y;
}				t_pt2d;

typedef struct	s_pt3d
{
	double		x;
	double		y;
	double		z;
}				t_pt3d;

typedef struct	s_ipt2d
{
	int			x;
	int			y;
}				t_ipt2d;

typedef struct	s_minidims
{
	int			ox;
	int			oy;
	int			width;
	int			height;
	int			block_size;
	int			border_thickness;
}				t_minidims;

typedef struct	s_wall
{
	int			cardinal;
	double		left_right_coef;
	double		up_down_coef;
	double		hit_x;
	double		hit_y;
	double		hit_z;
}				t_wall;

typedef struct	s_sprite_img
{
	t_img		im;
	t_pt2d		img_ratio;
	t_pt2d		img_offset;
}				t_sprite_img;

typedef struct		s_sprite
{
	char			type;
	t_pt2d			pos;
	t_sprite_img	*simg;
	t_list			*path;
	t_ipt2d			previous_block;
}					t_sprite;

typedef struct	s_path
{
	t_list		*steps;
	int			dist;
	int			visited;
}				t_path;

typedef struct	s_tpblock
{
	int			x;
	int			y;
	int			n_exits;
	int			exits[4];
}				t_tpblock;

typedef struct	s_special_blocks_counter
{
	int			n_telep;
	int			n_player_start;
}				t_special_blocks_counter;

typedef struct	s_map
{
	char		**grid;
	t_sprite	***pea_sprites_grid;
	t_list		***neighbors;
	int			width;
	int			height;
	int			peas_count;
	t_tpblock	*tpblocks;
	int			n_tpblocks;
}				t_map;

typedef struct			s_pack
{
	void				*mlx;
	void				*win;
	t_img				win_img[2];
	t_img				start_screen;
	t_img				victory_screen;
	t_img				lose_screen;
	int					game_on;
	int					mouse_on;
	t_minidims			mini;
	int					win_buffered;
	int					width;
	int					height;
	int					key_pressed;
	double				theta;
	double				theta_v;
	t_pt2d				pos;
	t_pt2d				dir;
	t_pt2d				dir_ortho;
	t_pt3d				pos3d;
	t_pt3d				dir3d;
	int					lives;
	int					lives_max;
	double				time_invul;
	int					touched_by_enemy;
	t_map				map;
	double				**dist_array;
	char				*cube_faces_fnames[6];
	int					floor_ceil_are_sprites;
	int					floor_color;
	int					ceil_color;
	t_img				cube_faces[6];
	t_img				portal_img;
	t_img				heart_img;
	t_img				heart_empty_img;
	char				*sprite_fname;
	t_list				*sprites;
	t_list				*enemies;
	t_sprite_img		*sprite_images;
	unsigned long long	nanosec;
	double				time_total;
	double				time_loop;
	double				time_restart;
	int					you_won;
	void				(*redraw_fun)(struct s_pack *p);
}						t_pack;

//hooks transition
void	start_menu(t_pack *p);
void	start_game(t_pack *p);
void	end_game(t_pack *p);
void	restart_game(t_pack *p);
//hooks render
int		key_press_hook(int kc, t_pack *p);
int		key_release_hook(int kc, t_pack *p);
int		motion_hook(int x, int y, t_pack *p);
int		expose_hook(t_pack *p);
int		loop_hook(t_pack *p);
//hooks render movement
void	handle_movement(t_pack *p);
//hooks render utils
void	collect_pea(t_pack *p);
void	assess_victory(t_pack *p);
void	assess_life(t_pack *p);
void	draw(t_pack *p);
// hooks render enemy
int		first_path_update(t_pack *p, t_sprite *enemy);
int		update_path(t_pack *p, t_sprite *enemy);
int		update_path_if_needed(t_pack *p, t_sprite *enemy);
int		move_all_enemies(t_pack *p);
//hooks start
void	put_start_screen(t_pack *p);
int		key_press_hook_menu(int kc, t_pack *p);
int		loop_hook_menu(t_pack *p);
//hooks end
void	put_end_screen(t_pack *p);
int		key_press_hook_end(int kc, t_pack *p);
int		loop_hook_end(t_pack *p);
//utils
void	swap(t_pack *p);
void	reset_clock(t_pack *p);
void	tick(t_pack *p);
t_img	img_from_ptr(void *img, int width, int height);
t_sprite	*sprite_at(t_list *sprite_list);
t_sprite_img	*sprite_img_from_type(t_pack *p, char type);
t_img	*buff_img(t_pack *p);
void	color_pix(t_img *im, int x, int y, unsigned int color);
int		color_pix_transparency(t_img *im, int x, int y, unsigned int color);
int		*get_pix_address(t_img *im, int x, int y);
void	rect_fill(t_img *im, int x1, int y1, int x2, int y2, int color);
void	col_fill(t_pack *p, t_wall *hit, int x, int visible_height);
void	rays_updown(t_pack *p, t_pt2d *ray_dir, int x, int visible_height);
void	sprite_fill(t_pack *p, t_sprite *sprite, int x_start, int width_screen, double dist);
void	clear_image(t_img *im);
int		in_bounds(int val, int max);
int		in_bounds2D(int x, int y, t_map *map);
int		in_bounds3D(int x, int y, int z, t_map *map);
int		is_tpblock(t_ipt2d block, t_map *map);
int		is_outside_or_wall(char block);
int		is_blocking(int x, int y, t_map *map);
double	sqnorm(double x, double y);
double	sqnorm3D(double x, double y, double z);
double	norm(double x, double y);
t_pt2d	add_vec(t_pt2d *v1, t_pt2d *v2);
int		is_wall(t_map *map, int x, int y);
t_pt2d	pt2d(double x, double y);
t_ipt2d	ipt2d(int x, int y);
t_ipt2d	round_pt2d(t_pt2d pt);
int		ipt2d_equal(t_ipt2d v1, t_ipt2d v2);
t_ipt2d	add_ipt2d(t_ipt2d a, t_ipt2d b);
t_ipt2d sub_ipt2d(t_ipt2d a, t_ipt2d b);
t_pt2d	add_pt2d(t_pt2d a, t_pt2d b);
void	add_pt2d_ptr(t_pt2d *a, t_pt2d b);
t_pt2d	mult_pt2d(t_pt2d a, double b);
int		cardinal_from_ipt2d(t_ipt2d delta);
t_tpblock	*tpblock_from_pos(t_map *map, int x, int y);
int		nothing_hook(void *nothing);
char	block_at(t_map *map, t_ipt2d coord);
int		iter_four_neighbors(t_map *map, t_ipt2d coord, void *obj,
			int (*fun)(t_map*, t_ipt2d, t_ipt2d, void*));
void	rotate3d_packdir(t_pack *p, double dth, double dth_v);
void	rotate(t_pt2d *v, double theta);
t_pt2d	sub_pt2d(t_pt2d a, t_pt2d b);
void	sub_pt2d_ptr(t_pt2d *a, t_pt2d b);
// gen_draw_utils
void draw_rect_image(t_img *win_im, t_img *im, t_ipt2d origin, int width);
void draw_menu_image(t_pack *p, t_img *menu_im);
// generic errors
int		malloc_error(void);
int		parse_error(void);
int		message_error(char *message);
int		file_not_found_error(char *fname);
//file_errors
int		file_error(char *fname);
int		file_error_free_lines_pack(t_list *scene_lines, t_pack *p);
int		free_clear_and_error(t_list **alst, char *line);
// lst_utils
t_sprite	*sprite_at(t_list *sprite_list);
t_ipt2d		*ipt2d_at(t_list *elem);
t_ipt2d		*path_destination(t_list *path);
void		pop_first(t_list **alst, t_ipt2d *res);
int			add_back_ipt2d_once(t_list **alst, t_ipt2d val);
t_list		*ipt2d_lstnew(t_ipt2d val);
// collision
void	correct_collision(t_pack *p);
void	move_and_correct(t_pack *p, t_pt2d movement);
//ray_march
double	ray_march(t_pt2d *pos, t_pt2d *dir, t_map *map, t_wall *hit);
double	ray_march3D_z(t_pt3d *pos, t_pt3d *dir, t_map *map, t_wall *hit);
// render
void	render(t_pack *p);
void	mloop(int argc, char **argv);
//minimap
void	render_minimap(t_pack *p);
//ia
int		update_shortest_path(t_map *map, t_sprite *sprite, t_ipt2d goal);
//ia path memory
int		path_copy(t_path *src, t_path *res);
void	clear_path(t_path *path);
void	clear_path_grid(t_map *map, t_path **pathgrid);
int		free_all_error(t_map *map, t_path **pathgrid, t_list **visit_fifo);
//ia path utils
int		*dist_at(t_path **pathgrid, t_ipt2d coord);
int		*visited_at(t_path **pathgrid, t_ipt2d coord);
t_list	**steps_at(t_path **pathgrid, t_ipt2d coord);
t_path	*path_at(t_path **pathgrid, t_ipt2d coord);
// map_objects_init
int		set_pack_map_properties_re(t_pack *p);
int		set_pack_map_properties_first(t_pack *p);
//free_others
void	free_img(void *mlx, t_img *im);
void	free_sprite(void *sprite_ptr);
void	free_win(void *mlx, void *win);
void	free_map(t_map *map);;
//free_pack
int		free_pack(t_pack *p);
int		free_pack_and_quit(t_pack *p);
// generate_bmp
int		generate_bmp(char *fname, t_pack *p);

/////
void print_ilist(t_list *lst);

#endif
