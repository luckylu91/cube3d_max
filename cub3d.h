#ifndef CUB3D_H
#define CUB3D_H

#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"
#include <math.h>
#include <errno.h>
#include <stdio.h> //perror
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
//
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
#define MAP_CHARS " 012NSEW"
#define ENEMIES "2"
#define SPRITES ".2"

#define ENEMY_SPEED 1.

#define KEY_W 122 // linux
#define KEY_A 113 // linux
#define KEY_S 115 // linux
#define KEY_D 100 // linux
#define KEY_ESC 65307 // linux
// #define KEY_ESC 53
// #define KEY_W 13
// #define KEY_A 0
// #define KEY_S 1
// #define KEY_D 2
#define KEY_LEFT 123
#define KEY_RIGHT 124
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
#define COLLISION_RADIUS .3 // < 0.5
// #define MINIMAP_MAX_SIZE 200
// #define MINI_BSIZE .05
// #define MINI_X .05
// #define MINI_Y .5

typedef union	u_argb
{
	uint32_t	a:8, r:8, g:8, b:8;
	uint32_t	color;
}				t_argb;

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
	int x;
	int y;
}				t_ipt2d;

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
	t_pt2d		img_ratio; //
	t_pt2d		img_offset; //
}				t_sprite_img;

typedef struct	s_sprite
{
	char		type;
	// t_img		im;
	//
	t_pt2d		pos;
	t_sprite_img *simg;
	t_list		*path;
	t_ipt2d		previous_block;
}				t_sprite;

typedef struct	s_path
{
	t_list	*steps;
	int		dist;
	int		visited;
}				t_path;

typedef struct	s_map
{
	char		**grid;
	t_sprite	***pea_sprites_grid;
	int			width;
	int			height;
	// t_pt2d		player_start;
	int			sprite_count;
	int			enemies_count;
	int			peas_count;
}				t_map;

typedef struct	s_pack
{
	void		*mlx;
	void		*win;
	t_img		win_img[2];
	//
	//void		*mini_win;
	//t_img		mini_win_img[2];
	t_pt2d		mini_origin;
	double		mini_width;
	int			win_buffered;
	int			width;
	int			height;
	int			key_pressed;
	double		theta;
	double		theta_v;
	t_pt2d		pos;
	t_pt2d		dir;
	t_pt2d		dir_ortho;
	t_pt3d		pos3d;
	t_pt3d		dir3d;
	t_map		map;
	double		**dist_array; // free
	char		*cube_faces_fnames[6]; // free
	int			floor_ceil_are_sprites;
	int			floor_color;
	int			ceil_color;
	t_img		cube_faces[6];
	// t_sprite	*sprites;
	// int			sprites_number;
	// t_sprite	**enemies;
	// int			enemies_number;
	t_list			*sprites;
	t_list			*enemies;
	t_sprite_img	*sprite_images;
	unsigned long long	nanosec;
	double		time_total;
	double		time_loop;
}				t_pack;

//hooks
int		key_press_hook(int kc, t_pack *p);
int		key_release_hook(int kc, t_pack *p);
int		loop_hook(t_pack *p);
int		motion_hook(int x, int y, t_pack *p);

//utils
void	swap(t_pack *p);
void	tick(t_pack *p);
t_sprite *sprite_at(t_list *sprite_list);
t_img	img_from_ptr(void *img, int width, int height);
t_sprite_img *sprite_img_from_type(t_pack *p, char type);
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
double	sqnorm(double x, double y);
double	sqnorm3D(double x, double y, double z);
double	norm(double x, double y);
t_pt2d	add_vec(t_pt2d *v1, t_pt2d *v2);
int		is_wall(t_map *map, int x, int y);
t_pt2d	pt2d(double x, double y);
t_ipt2d	ipt2d(int x, int y);
int		ipt2d_equal(t_ipt2d v1, t_ipt2d v2);

// lst_utils
t_sprite	*sprite_at(t_list *sprite_list);
t_ipt2d		*ipt2d_at(t_list *elem);
t_ipt2d		*path_destination(t_list *path);
void		pop_first(t_list **alst, t_ipt2d *res);

// collision
void	correct_collision(t_pack *p);

//ray_march
double	ray_march(t_pt2d *pos, t_pt2d *dir, t_map *map, t_wall *hit);
double	ray_march3D_z(t_pt3d *pos, t_pt3d *dir, t_map *map, t_wall *hit);

// render
void	render(t_pack *p);
void	mloop();

//minimap
void	render_minimap(t_pack *p);

//ia
int		update_shortest_path(t_map *map, t_sprite *sprite, t_ipt2d goal);

//free_pack
void	free_sprite(void *sprite);
int		free_pack(t_pack *p);
int		free_pack_and_quit(t_pack *p);

#endif