#include "cub3d.h"
//
#include <time.h>

#define SCREEN_DIST 2.
#define SCREEN_WIDTH_SIZE 5.
#define WALL_SIZE 1.

int color_from_side(int cardinal)
{
	if (cardinal == NORTH) // WHITE
		return (0X00FFFFFF);
	if (cardinal == SOUTH) // RED
		return (0X00FF0000);
	if (cardinal == EAST) // GREEN
		return (0X0000FF00);
	if (cardinal == WEST) // BLUE
		return (0X000000FF);
	if (cardinal == CEIL) // PURPLE
		return (0X007F007F);
	if (cardinal == FLOOR)
		return (0X00007F7F);
	return (0X007F7F7F);
}

static void print_pt3d(t_pt3d p, char *s)
{
	printf("%s(x: %.2f, y: %.2f, z: %.2f)\n", s, p.x, p.y, p.z);
}

static inline t_pt3d mult_ptr1(t_pt3d *v, double a)
{
	t_pt3d res;
	res.x = v->x * a;
	res.y = v->y *  a;
	res.z = v->z *  a;
	return (res);
}

static inline t_pt3d add(t_pt3d a, t_pt3d b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

static inline void add_ptr1(t_pt3d *dest, t_pt3d b)
{
	dest->x += b.x;
	dest->y += b.y;
	dest->z += b.z;
}

static inline void add_ptr2(t_pt3d *dest, t_pt3d *b)
{
	dest->x += b->x;
	dest->y += b->y;
	dest->z += b->z;
}

void render(t_pack *p)
{
	t_wall	hit;
	t_pt3d	ray_dir;
	t_pt3d	ray_dir_up;
	t_pt3d	dir_h;
	t_pt3d	dir_v;
	int		i;
	int		j;
	double	sqdist;
	double	delta_h;
	double	delta_v;
	//
	static int beg_cpt = 0;
	static clock_t outside, start_fun, start_while, end, end_outside, start_ray;
	double ray_time = 0.;
	if (beg_cpt < 10)
	{
		printf("\ncall no %d to render function\n", beg_cpt);
		if (beg_cpt != 0)
		{
			end_outside = clock();
			printf("outside of render : %.6fs\n", (double)(end_outside - outside) / CLOCKS_PER_SEC);
		}
		start_fun = clock();
	}

	delta_h = SCREEN_WIDTH_SIZE / p->width;
	dir_h.x = sin(p->theta) * delta_h;
	dir_h.y = cos(p->theta) * delta_h;
	dir_h.z = 0.;
	delta_v = (SCREEN_WIDTH_SIZE * p->height / p->width) / p->height;
	dir_v.x = -cos(p->theta) * sin(p->theta_v) * delta_v;
	dir_v.y = sin(p->theta) * sin(p->theta_v) * delta_v;
	dir_v.z = cos(p->theta_v) * delta_v;
	ray_dir = mult_ptr1(&p->dir3d, SCREEN_DIST);
	add_ptr1(&ray_dir, mult_ptr1(&dir_h, -p->width / 2));
	add_ptr1(&ray_dir, mult_ptr1(&dir_v, -p->height / 2));
	ray_dir_up = ray_dir;
	if (beg_cpt < 10)
		start_while = clock();
	i = -1;
	while (++i < p->width)
	{
		ray_dir = ray_dir_up;
		j = -1;
		while (++j < p->height)
		{
			//start_ray = clock();
			sqdist = ray_march3D(&p->pos3d, &ray_dir, &p->map, &hit);
			//ray_time += (double)(clock() - start_ray) / CLOCKS_PER_SEC;
			if (sqdist >= 0.)
				color_pix(&p->win_img[p->win_buffered], i, j,
					*get_pix_address(
						&p->cube_faces[hit.cardinal],
						hit.left_right_coef * p->cube_faces[hit.cardinal].width,
						hit.up_down_coef * p->cube_faces[hit.cardinal].height));
				//color_pix(p->win_img[p->win_buffered], i, j, color_from_side(hit.cardinal));
				//WEIRD color_pix(p->win_img[p->win_buffered], i, j, (int)(256 * tanh(ray_time)) << 16);
			add_ptr2(&ray_dir, &dir_v);
		}
		add_ptr2(&ray_dir_up, &dir_h);
	}
	if (beg_cpt < 10)
	{
		end = clock();
		printf("main loop duration : %.6fs\n", (double)(end - start_while) / CLOCKS_PER_SEC);
		printf("render whole duration : %.6fs\n", (double)(end - start_fun) / CLOCKS_PER_SEC);
		//printf("total rays duration : %.6fs\n", ray_time);
		outside = clock();
		beg_cpt++;
	}
}