#include <time.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"

#define WIDTH 12
#define HEIGHT 8
#define SIZE 10

#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_LEFT 123
#define KEY_RIGHT 124

#define KEYMASK_W (1 << 0)
#define KEYMASK_A (1 << 1)
#define KEYMASK_S (1 << 2)
#define KEYMASK_D (1 << 3)
#define KEYMASK_LEFT (1 << 4)
#define KEYMASK_RIGHT (1 << 5)

#define AWAY_COLOR 0X0000AAAA
#define CATCH_COLOR 0X00FF7777

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

typedef struct	s_data
{
	void *mlx;
	void *win;
	t_img win_imgs[2];
	int win_buff;
	double x;
	double y;
	double x_enemy;
	double y_enemy;
	int		enemy_color;
	int		key_pressed;
	unsigned long long instant;
}				t_data;

/////


int		in_bounds(int val, int max)
{
	return ((0 <= val) && (val < max));
}

void	color_pix(t_img *im, int x, int y, int color)
{
	if (in_bounds(x, im->width) && in_bounds(y, im->height))
		*((int*)(im->data + x * im->bpp / 8 + y * im->lsize)) = color;
}

void	rect_fill(t_img *im, int x1, int y1, int x2, int y2, int color)
{
	int i, j;

	for (i = x1; i < x2; i++)
	{
		for (j = y1; j < y2; j++)
		{
			color_pix(im, i, j, color);
		}
	}
}

void	clear_image(t_img *im)
{
	int x;
	int y;

	x = 0;
	while (x < im->width)
	{
		y = 0;
		while (y < im->height)
		{
			color_pix(im, x, y, 0);
			y++;
		}
		x++;
	}
}

void	swap(t_data *d)
{
	mlx_put_image_to_window(d->mlx, d->win, d->win_imgs[d->win_buff].img, 0, 0);
	d->win_buff = (d->win_buff + 1) % 2;
	clear_image(&d->win_imgs[d->win_buff]);
}

t_img img_from_ptr(void *img, int width, int height)
{
	t_img	res;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	char	*img_addr;

	img_addr = mlx_get_data_addr(img, &bits_per_pixel, &line_size, &endian);
	res.img = img;
	res.data = img_addr;
	res.bpp = bits_per_pixel;
	res.lsize = line_size;
	res.endian = endian;
	res.width = width;
	res.height = height;
	return (res);
}
/////

// int main_hook(t_data *d)
// {
// 	struct timespec req;
// 	struct timespec rem;
// 	double elapsed_sec;

// 	if (d->key_pressed & KEYMASK_W && d->y > 0)
// 		d->y--;
// 	else if (d->key_pressed & KEYMASK_A && d->x > 0)
// 		d->x++;
// 	else if (d->key_pressed & KEYMASK_S && d->y < HEIGHT - 1)
// 		d->y++;
// 	else if (d->key_pressed & KEYMASK_D && d->x < WIDTH - 1)
// 		d->x++;
// 	rect_fill(&d->win_imgs[d->win_buff], SIZE * d->x, SIZE * d->y, SIZE * (d->x + 1), SIZE * (d->y + 1), 0X00FFFFFF);
// 	elapsed_sec = (double)(clock() - d->instant) / CLOCKS_PER_SEC;
// 	printf("elapsed : %.9fs\n", elapsed_sec);
// 	if (elapsed_sec < 1.)
// 	{
// 		printf("waiting %.9fs\n", 1. - elapsed_sec);
// 		req.tv_sec = 0;
// 		req.tv_nsec = (long)(1000000000. * (1. - elapsed_sec));
// 		nanosleep(&req, &rem);
// 		while (rem.tv_nsec > 10)
// 		{
// 			printf("Interrupted, rem = %ld.%.9lds\n", rem.tv_sec, rem.tv_nsec);
// 			req = rem;
// 			nanosleep(&req, &rem);
// 		}
// 	}
// 	swap(d);
// 	d->instant = clock();
// 	return (0);
// }

void update_enemy(t_data *d)
{
	double dx, dy, distx, disty;

	if ((int)d->x_enemy == (int)d->x && (int)d->y_enemy == (int)d->y)
		return ;
	dx = d->x - d->x_enemy;
	dy = d->y - d->y_enemy;
	if (fabs(dx) > fabs(dy))
		d->x_enemy += (dx > 0 ? 1 : -1);
	else
		d->y_enemy += (dy > 0 ? 1 : -1);
}

int main_hook_bis(t_data *d)
{
	static double enemy_secs = 0.;
	static double player_secs = 0.;
	double elapsed_secs;

	elapsed_secs = (double)(clock_gettime_nsec_np(CLOCK_REALTIME) - d->instant) / 1000000000L;
	d->instant = clock_gettime_nsec_np(CLOCK_REALTIME);
	enemy_secs += elapsed_secs;
	if (enemy_secs >= .8)
	{
		enemy_secs -= .8;
		update_enemy(d);
	}
	player_secs += elapsed_secs;
	if (player_secs >= .8 / 10)
	{
		player_secs -= .8 / 10;
		if ((d->key_pressed & KEYMASK_W) && d->y >= .1) // 1. / 10
			d->y -= .1;
		else if ((d->key_pressed & KEYMASK_A) && d->x >= .1)
			d->x -= .1;
		else if ((d->key_pressed & KEYMASK_S) && d->y < HEIGHT - .1)
			d->y += .1;
		else if ((d->key_pressed & KEYMASK_D) && d->x < WIDTH - .1)
			d->x += .1;
	}
	//printf("enemy secs = %.3f\nplayer_secs = %.3f\n", enemy_secs, player_secs);
	if ((int)d->x_enemy == (int)d->x && (int)d->y_enemy == (int)d->y)
		d->enemy_color = CATCH_COLOR;
	else
		d->enemy_color = AWAY_COLOR;
	rect_fill(&d->win_imgs[d->win_buff],
		SIZE * d->x,
		SIZE * d->y,
		SIZE * (d->x + 1),
		SIZE * (d->y + 1),
		0X00FFFFFF);
	rect_fill(&d->win_imgs[d->win_buff],
		SIZE * d->x_enemy,
		SIZE * d->y_enemy,
		SIZE * (d->x_enemy + 1),
		SIZE * (d->y_enemy + 1),
		d->enemy_color);
	swap(d);
	return (0);
}

int keypress_hook(int kc, t_data *d)
{
	if (kc == KEY_W)
		d->key_pressed |= KEYMASK_W;
	else if (kc == KEY_A)
		d->key_pressed |= KEYMASK_A;
	else if (kc == KEY_S)
		d->key_pressed |= KEYMASK_S;
	else if  (kc == KEY_D)
		d->key_pressed |= KEYMASK_D;
	return (0);
}

int keyrelease_hook(int kc, t_data *d)
{
	if (kc == KEY_W)
		d->key_pressed &= ~KEYMASK_W;
	else if (kc == KEY_A)
		d->key_pressed &= ~KEYMASK_A;
	else if (kc == KEY_S)
		d->key_pressed &= ~KEYMASK_S;
	else if  (kc == KEY_D)
		d->key_pressed &= ~KEYMASK_D;
	return (0);
}

int main()
{
	void *mlx;
	void *win;
	void *win_img1;
	void *win_img2;
	int wpx = WIDTH * SIZE;
	int hpx = HEIGHT * SIZE;

	mlx = mlx_init();
	win = mlx_new_window(mlx, wpx, hpx, "TIME");
	win_img1 = mlx_new_image(mlx, wpx, hpx);
	win_img2 = mlx_new_image(mlx, wpx, hpx);
	t_data d = {
		.mlx = mlx,
		.win = win,
		.win_imgs = {img_from_ptr(win_img1, wpx, hpx), img_from_ptr(win_img2, wpx, hpx)},
		.win_buff = 0,
		.instant = clock_gettime_nsec_np(CLOCK_REALTIME),
		.x = WIDTH / 2,
		.y = HEIGHT / 2,
		.x_enemy = 0,
		.y_enemy = 0,
		.enemy_color = AWAY_COLOR
	};
	mlx_loop_hook(mlx, main_hook_bis, &d);
	mlx_hook(win, 2, 1L << 0, keypress_hook, &d);
	mlx_hook(win, 3, 1L << 1, keyrelease_hook, &d);
	mlx_loop(mlx);
}