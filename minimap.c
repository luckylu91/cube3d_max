#include "cub3d.h"

#define COLOR_MINI_WALL 0X000E18A2

// TODO crete circle img only once

// img creation
int create_dot_img(void *mlx, t_img *im, int size, unsigned int color)
{
	void *img;
	double x;
	double y;
	double y_halflen;

	if (!(img = mlx_new_image(mlx, size, size)))
		return (-1);
	*im = img_from_ptr(img, size, size);
	x = .5 - 1;
	while (++x < size)
	{
		// y_halflen = sqrt((size - 1) * (size - 1) / 4. - (x - size / 2.) * (x - size / 2.));
		y_halflen = sqrt(x * (size - x) - size / 2. + .25);
		y = size / 2. - y_halflen + .5 - 1;
		while (++y < size / 2. + y_halflen - .5)
			color_pix(im, (int)x, (int)y, color);
	}
	return (1);
}

void draw_circle(t_img *im, t_pt2d offsets, int size, double ratio, unsigned int color)
{
	t_pt2d im_coord;

	if (ratio > 1.)
		ratio = 1.;
	else if (ratio < 0.)
		ratio = 0;
	im_coord.x = - 1;
	while (++im_coord.x < size)
	{
		im_coord.y = - 1;
		while (++im_coord.y < size)
		{
			if (sqnorm(im_coord.x - size / 2, im_coord.y - size / 2) <= size * size * ratio * ratio / 4.)
				color_pix(im, im_coord.x + offsets.x, im_coord.y + offsets.y, color);
		}
	}
}

void draw_pacu(t_pack *p, double mouth_angle, double mouth_openness, unsigned int color)
{
	t_ipt2d	delta;
	t_pt2d pacu_coord;
	t_pt2d offsets;
	int block_size;

	block_size = p->mini_width / p->map.width;
	offsets.x = (int)p->pos.x * block_size + p->mini_origin.x;
	offsets.y = (int)p->pos.y * block_size + p->mini_origin.y;
	delta.x = - 1;
	while (++delta.x < block_size)
	{
		delta.y = - 1;
		while (++delta.y < block_size)
		{
			pacu_coord.x = (delta.x - block_size / 2.) * cos(mouth_angle)
							- (delta.y - block_size / 2.) * sin(mouth_angle);
			pacu_coord.y = (delta.x - block_size / 2.) * sin(mouth_angle)
							+ (delta.y - block_size / 2.) * cos(mouth_angle);
			if (sqnorm(pacu_coord.x, pacu_coord.y) <= pow(block_size, 2) / 4.
					&& (pacu_coord.x < 0
						|| fabs(pacu_coord.y) >= sin(mouth_openness) * pacu_coord.x))
				color_pix(
					&p->win_img[p->win_buffered],
					delta.x + offsets.x,
					delta.y + offsets.y,
					color);
		}
	}
}

void draw_one_enemy(t_pack *p, t_sprite *sprite)
{
	t_img	sprite_im;
	t_ipt2d	offsets;
	t_ipt2d sprite_coord;
	t_ipt2d	delta;
	int		block_size;

	block_size = p->mini_width / p->map.width;
	sprite_im = sprite->simg->im;
	offsets.x = (int)(sprite->pos.x) * block_size + p->mini_origin.x;
	offsets.y = (int)(sprite->pos.y) * block_size + p->mini_origin.y;
	delta.x = -1;
	while (++delta.x < block_size)
	{
		delta.y = -1;
		while (++delta.y < block_size)
		{
			sprite_coord.x = delta.x * (double)sprite_im.width / block_size;
			sprite_coord.y = delta.y * (double)sprite_im.height / block_size;
			color_pix_transparency(
				&p->win_img[p->win_buffered],
				offsets.x + delta.x,
				offsets.y + delta.y,
				*get_pix_address(&sprite_im, sprite_coord.x, sprite_coord.y));
		}
	}
}

void draw_enemies(t_pack *p)
{
	t_list		*enemy_lst;
	t_sprite	*enemy;

	enemy_lst = p->enemies;
	while (enemy_lst)
	{
		enemy = (t_sprite*)(enemy_lst->content);
		draw_one_enemy(p, enemy);
		enemy_lst = enemy_lst->next;
	}
}

// TODO ? only clear pacu & ghosts
void render_minimap(t_pack *p)
{
	int x;
	int y;
	t_pt2d pacu_offset;
	int block_size;

	block_size = p->mini_width / p->map.width;
	//clear_image(&p->mini_win_img[p->win_buffered]);
	rect_fill(
		&p->win_img[p->win_buffered],
		p->mini_origin.x,
		p->mini_origin.y,
		p->mini_origin.x + p->mini_width,
		p->mini_origin.y + p->mini_width * p->map.height / p->map.width,
		0x00000000
	);
	x = -1;
	while (++x < p->map.width)
	{
		y = -1;
		while (++y < p->map.height)
		{
			if (p->map.grid[x][y] == WALL)
			{
				//center
				rect_fill(
					&p->win_img[p->win_buffered],
					p->mini_origin.x + (x + .4) * block_size,
					p->mini_origin.y + (y + .4) * block_size,
					p->mini_origin.x + (x + .6) * block_size,
					p->mini_origin.y + (y + .6) * block_size,
					COLOR_MINI_WALL
				);
				// retro_rect fill to do only x-1,y and x, y-1
				if (in_bounds2D(x - 1, y, &p->map) && p->map.grid[x - 1][y] == WALL)
					rect_fill(
						&p->win_img[p->win_buffered],
						p->mini_origin.x + (x - .6) * block_size,
						p->mini_origin.y + (y + .4) * block_size,
						p->mini_origin.x + (x + .4) * block_size,
						p->mini_origin.y + (y + .6) * block_size,
						COLOR_MINI_WALL
					);
				if (in_bounds2D(x, y - 1, &p->map) && p->map.grid[x][y - 1] == WALL)
					rect_fill(
						&p->win_img[p->win_buffered],
						p->mini_origin.x + (x + .4) * block_size,
						p->mini_origin.y + (y - .6) * block_size,
						p->mini_origin.x + (x + .6) * block_size,
						p->mini_origin.y + (y + .4) * block_size,
						COLOR_MINI_WALL
					);
			}
			else if (p->map.pea_sprites_grid[x][y])
			{
				draw_circle(
					&p->win_img[p->win_buffered],
					pt2d(p->mini_origin.x + x * block_size, p->mini_origin.y + y * block_size),
					block_size,
					.5,
					0x00AA33AA
					);
			}
		}
	}
	draw_enemies(p);
	pacu_offset.x = p->mini_origin.x + floor(p->pos.x) * block_size;
	pacu_offset.y = p->mini_origin.y + floor(p->pos.y) * block_size;
	draw_pacu(
		p,
		p->theta,
		M_PI / 4 * pow(cos(5 * p->time_total), 2),
		0X00F5C352
	);
}