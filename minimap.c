#include "cub3d.h"

#define COLOR_MINI_WALL 0X000E18A2
#define COLOR_PORTAL 0X005EE51B

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
	// int block_size;

	//block_size = p->mini_width / p->map.width;
	offsets.x = (int)p->pos.x * p->mini.block_size + p->mini.ox;
	offsets.y = (int)p->pos.y * p->mini.block_size + p->mini.oy;
	delta.x = - 1;
	while (++delta.x < p->mini.block_size)
	{
		delta.y = - 1;
		while (++delta.y < p->mini.block_size)
		{
			pacu_coord.x = (delta.x - p->mini.block_size / 2.) * cos(mouth_angle)
							- (delta.y - p->mini.block_size / 2.) * sin(mouth_angle);
			pacu_coord.y = (delta.x - p->mini.block_size / 2.) * sin(mouth_angle)
							+ (delta.y - p->mini.block_size / 2.) * cos(mouth_angle);
			if (sqnorm(pacu_coord.x, pacu_coord.y) <= pow(p->mini.block_size, 2) / 4.
					&& (pacu_coord.x < 0
						|| fabs(pacu_coord.y) >= sin(mouth_openness) * pacu_coord.x))
				color_pix(
					buff_img(p),
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
	// int		p->mini.block_size;

	//p->mini.block_size = p->mini_width / p->map.width;
	sprite_im = sprite->simg->im;
	offsets.x = (int)(sprite->pos.x) * p->mini.block_size + p->mini.ox;
	offsets.y = (int)(sprite->pos.y) * p->mini.block_size + p->mini.oy;
	delta.x = -1;
	while (++delta.x < p->mini.block_size)
	{
		delta.y = -1;
		while (++delta.y < p->mini.block_size)
		{
			sprite_coord.x = delta.x * (double)sprite_im.width / p->mini.block_size;
			sprite_coord.y = delta.y * (double)sprite_im.height / p->mini.block_size;
			color_pix_transparency(
				buff_img(p),
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

void minimap_border(t_pack *p)
{
	rect_fill(
		buff_img(p),
		p->mini.ox - p->mini.border_thickness,
		p->mini.oy - p->mini.border_thickness,
		p->mini.ox + p->mini.width + p->mini.border_thickness,
		p->mini.oy,
		0X00FFFFFF
	);
	rect_fill(
		buff_img(p),
		p->mini.ox - p->mini.border_thickness,
		p->mini.oy + p->mini.height,
		p->mini.ox + p->mini.width + p->mini.border_thickness,
		p->mini.oy + p->mini.height + p->mini.border_thickness,
		0X00FFFFFF
	);
	rect_fill(
		buff_img(p),
		p->mini.ox - p->mini.border_thickness,
		p->mini.oy,
		p->mini.ox,
		p->mini.oy + p->mini.height,
		0X00FFFFFF
	);
	rect_fill(
		buff_img(p),
		p->mini.ox + p->mini.width,
		p->mini.oy,
		p->mini.ox + p->mini.width + p->mini.border_thickness,
		p->mini.oy + p->mini.height,
		0X00FFFFFF
	);
}

int		draw_neighbor_fun(t_map *map, t_ipt2d coord, t_ipt2d coord2, void *pack_ptr)
{
	int		wall_color;
	t_pack	*p;
	t_ipt2d	ul_corner;
	t_ipt2d	lr_corner;

	if (!in_bounds2D(coord2.x, coord2.y, map) || !is_blocking(coord2.x, coord2.y, map))
		return (1);
	p = (t_pack*)pack_ptr;
	wall_color = (block_at(map, coord) == WALL) ? COLOR_MINI_WALL : COLOR_PORTAL;
	coord2 = sub_ipt2d(coord2, coord);
	if (coord2.x == 0)
	{
		ul_corner.x = (coord.x + .4) * p->mini.block_size;
		lr_corner.x = (coord.x + .6) * p->mini.block_size;
		if (coord2.y == -1)
		{
			ul_corner.y = coord.y * p->mini.block_size;
			lr_corner.y = (coord.y + .4) * p->mini.block_size;
		}
		else
		{
			ul_corner.y = (coord.y + .6) * p->mini.block_size;
			lr_corner.y = (coord.y + 1.) * p->mini.block_size;
		}
	}
	else
	{
		ul_corner.y = (coord.y + .4) * p->mini.block_size;
		lr_corner.y = (coord.y + .6) * p->mini.block_size;
		if (coord2.x == -1)
		{
			ul_corner.x = coord.x * p->mini.block_size;
			lr_corner.x = (coord.x + .4) * p->mini.block_size;
		}
		else
		{
			ul_corner.x = (coord.x + .6) * p->mini.block_size;
			lr_corner.x = (coord.x + 1.) * p->mini.block_size;
		}
	}
	rect_fill(
		buff_img(p),
		p->mini.ox + ul_corner.x,
		p->mini.oy + ul_corner.y,
		p->mini.ox + lr_corner.x,
		p->mini.oy + lr_corner.y,
		wall_color
	);
	return (1);
}

// TODO ? only clear pacu & ghosts
void render_minimap(t_pack *p)
{
	int x;
	int y;
	t_pt2d pacu_offset;
	int wall_color;
	// int block_size;

	//block_size = p->mini_width / p->map.width;
	//clear_image(&p->mini_win_img[p->win_buffered]);
	rect_fill(
		buff_img(p),
		p->mini.ox,
		p->mini.oy,
		p->mini.ox + p->mini.width,
		p->mini.oy + p->mini.height,
		0X00000000
	);
	x = -1;
	while (++x < p->map.width)
	{
		y = -1;
		while (++y < p->map.height)
		{
			if (p->map.grid[x][y] == WALL || p->map.grid[x][y] == TELEP)
			{
				iter_four_neighbors(&p->map, ipt2d(x, y), p, &draw_neighbor_fun);
				wall_color = (p->map.grid[x][y] == WALL) ? COLOR_MINI_WALL : COLOR_PORTAL;
				//center
				rect_fill(
					buff_img(p),
					p->mini.ox + (x + .4) * p->mini.block_size,
					p->mini.oy + (y + .4) * p->mini.block_size,
					p->mini.ox + (x + .6) * p->mini.block_size,
					p->mini.oy + (y + .6) * p->mini.block_size,
					wall_color
				);
				// // retro_rect fill to do only x-1,y and x, y-1
				// if (in_bounds2D(x - 1, y, &p->map) && p->map.grid[x - 1][y] == WALL)
				// 	rect_fill(
				// 		buff_img(p),
				// 		p->mini.ox + (x - .6) * p->mini.block_size,
				// 		p->mini.oy + (y + .4) * p->mini.block_size,
				// 		p->mini.ox + (x + .4) * p->mini.block_size,
				// 		p->mini.oy + (y + .6) * p->mini.block_size,
				// 		wall_color
				// 	);
				// if (in_bounds2D(x, y - 1, &p->map) && p->map.grid[x][y - 1] == WALL)
				// 	rect_fill(
				// 		buff_img(p),
				// 		p->mini.ox + (x + .4) * p->mini.block_size,
				// 		p->mini.oy + (y - .6) * p->mini.block_size,
				// 		p->mini.ox + (x + .6) * p->mini.block_size,
				// 		p->mini.oy + (y + .4) * p->mini.block_size,
				// 		wall_color
				// 	);
			}
			else if (p->map.pea_sprites_grid[x][y])
			{
				draw_circle(
					buff_img(p),
					pt2d(p->mini.ox + x * p->mini.block_size, p->mini.oy + y * p->mini.block_size),
					p->mini.block_size,
					.5,
					0x00AA33AA);
			}
		}
	}
	draw_enemies(p);
	pacu_offset.x = p->mini.ox + floor(p->pos.x) * p->mini.block_size;
	pacu_offset.y = p->mini.oy + floor(p->pos.y) * p->mini.block_size;
	draw_pacu(
		p,
		p->theta,
		M_PI / 4 * pow(cos(5 * p->time_total), 2),
		0X00F5C352
	);
	minimap_border(p);
}
