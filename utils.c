#include "cub3d.h"

void	swap(t_pack *p)
{
	mlx_put_image_to_window(p->mlx, p->win, p->win_img[p->win_buffered].img, 0, 0);
	// mlx_put_image_to_window(p->mlx, p->mini_win, p->mini_win_img[p->win_buffered].img, 0, 0);
	p->win_buffered = (p->win_buffered + 1) % 2;
}

void	tick(t_pack *p)
{
	p->time_loop = (double)(clock_gettime_nsec_np(CLOCK_REALTIME) - p->nanosec) / 1000000000L;
	p->time_total += p->time_loop;
	p->nanosec = clock_gettime_nsec_np(CLOCK_REALTIME);
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

t_sprite_img *sprite_img_from_type(t_pack *p, char type)
{
	char		*sprites_str;

	sprites_str = SPRITES;
	return (p->sprite_images + (ft_strchr(sprites_str, type) - sprites_str));
}

int		*get_pix_address(t_img *im, int x, int y)
{
	return ((int*)(im->data + x * im->bpp / 8 + y * im->lsize));
}

void	color_pix(t_img *im, int x, int y, unsigned int color)
{
	if (in_bounds(x, im->width) && in_bounds(y, im->height))
		*get_pix_address(im, x, y) = color;
}

int		color_pix_transparency(t_img *im, int x, int y, unsigned int color)
{
	static int i_db = 0;
	t_argb	argb;
	t_argb	*argb_pix;
	int 	*pix;

	if (!in_bounds(x, im->width) || !in_bounds(y, im->height))
		return (0);
	if (color >> 24 < 30)
	{
		*get_pix_address(im, x, y) = color;
		return (1);
	}
	return (0);
	// argb.color = color;
	// argb_pix = (t_argb*)get_pix_address(im, x, y);
	// argb_pix->r = (argb.r * (127 - argb.a) + argb_pix->r * (127 - argb.a)) / 127;
	// argb_pix->g = (argb.g * argb.a + argb_pix->g * (127 - argb.a)) / 127;
	// argb_pix->b = (argb.b * argb.a + argb_pix->b * (127 - argb.a)) / 127;

	// pix = get_pix_address(im, x, y);
	// argb[0].color = color;
	// argb[1].color = *pix;
	// argb[1].a = 0;
	// argb[1].r = (argb[0].r * (255 - argb[0].a) + argb[1].r * argb[0].a) / 255;
	// argb[1].g = (argb[0].g * (255 - argb[0].a) + argb[1].g * argb[0].a) / 255;
	// argb[1].b = (argb[0].b * (255 - argb[0].a) + argb[1].b * argb[0].a) / 255;
	// *pix = argb[1].color;
	
	// if (i_db < 100 && argb.a > 0)
	// {
	// 	printf("color.a = %x\n", (unsigned char)argb.a);
	// 	i_db++;
	// }
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

void	col_fill(t_pack *p, t_wall *hit, int x, int visible_height)
{
	t_img	im_wall;
	int		img_x;
	int		y;
	int		y2;
	double	img_yf;
	double	dy;

	im_wall = p->cube_faces[hit->cardinal];
	img_x = hit->left_right_coef * im_wall.width;
	dy = (double)im_wall.height / (visible_height + 1);
	y = (p->height - visible_height) / 2;
	y2 = p->height - 1 - y;
	img_yf = 0;
	if (visible_height >= p->height)
	{
		y = 0;
		y2 = p->height - 1;
		img_yf = (double)((visible_height - p->height) / 2) * im_wall.height / visible_height;
	}
	while (y <= y2)
	{
		// if ((int)yf >= im_wall.height)
		// 	printf("visible_height %s p->height\n", (visible_height > p->height ? ">" : "<="));
		color_pix(&p->win_img[p->win_buffered], x, y, *get_pix_address(&im_wall, img_x, img_yf));
		img_yf += dy;
		y++;
	}
}

/// FLOOR / CEIL


void	rays_updown(t_pack *p, t_pt2d *ray_dir, int x, int visible_height)
{
	t_wall hit;
	t_pt3d ray_dir3d;
	int y;

	if (visible_height >= p->height)
		return ;
	ray_dir3d.x = ray_dir->x;
	ray_dir3d.y = ray_dir->y;
	y = -1;
	while (++y <= (p->height - visible_height) / 2)
	{
		ray_dir3d.z = SCREEN_WIDTH_SIZE / p->width * (p->height / 2 - y);
		ray_march3D_z(&p->pos3d, &ray_dir3d, &p->map, &hit);
		color_pix(
			&p->win_img[p->win_buffered],
			x,
			y,
			(((int)(hit.left_right_coef * 255)) << 16) + ((int)(hit.up_down_coef * 255))
			// *get_pix_address(
			// 	&p->cube_faces[CEIL],
			// 	hit.left_right_coef * p->cube_faces[CEIL].width,
			// 	hit.up_down_coef * p->cube_faces[CEIL].height
			// )
		);
		color_pix(
			&p->win_img[p->win_buffered],
			x,
			p->height - 1 - y,
			(((int)(hit.left_right_coef * 255)) << 16) + ((int)(hit.up_down_coef * 255))
			// *get_pix_address(
			// 	&p->cube_faces[FLOOR],
			// hit.left_right_coef * p->cube_faces[CEIL].width,
			// hit.up_down_coef * p->cube_faces[CEIL].height
			// )
		);
	}
}

// static	int sprite_offset_x(t_sprite *sprite, int total_size_screen)
// {
// 	double ratio_part;
// 	double offset_part;

// 	ratio_part = (total_size_screen * (1. - sprite->img_ratio.x)) / 2;
// 	offset_part = sprite->img_offset.x * (double)(total_size_screen / sprite->im.width);
// 	return ((int)(ratio_part + offset_part));
// }

// static int sprite_size_y(t_sprite *sprite, int total_size_screen)
// {
// 	double ratio_part;
// 	double offset_part;

// 	ratio_part = (total_size_screen * sprite->img_ratio.y);
// 	offset_part = -sprite->img_offset.y * (double)(total_size_screen / sprite->im.height);
// 	return ((int)(ratio_part + offset_part));
// }

/// END (FLOOR / CEIL)
void	sprite_fill(t_pack *p, t_sprite *sprite, int x_start, int size_screen, double dist)
{
	int x;
	int x_img;
	int y;
	int y_start;
	int y_img;
	t_pt2d size;
	t_pt2d offsets;
	t_pt2d im_screen_ratio;
	// double im_screen_ratio[2];
	//double height_screen;

	// assume height 1 sprites
	// im_screen_ratio[0] = (double)size_screen / (sprite->im.width * sprite->img_ratio.x);
	// im_screen_ratio[1] = (double)size_screen / (sprite->im.height * sprite->img_ratio.y);
	size.x = size_screen * sprite->simg->img_ratio.x;
	size.y = size_screen * sprite->simg->img_ratio.y;
	offsets.x = sprite->simg->img_offset.x * (double)(size_screen / sprite->simg->im.width);
	offsets.y = sprite->simg->img_offset.x * (double)(size_screen / sprite->simg->im.height);
	x_start += (size_screen - size.x) / 2 + offsets.x;
	y_start = (p->height - size.y) / 2 + offsets.y;
	im_screen_ratio.x = sprite->simg->im.width / size.x;
	im_screen_ratio.y = sprite->simg->im.height / size.y;
	//height_screen = im_screen_ratio[0] * sprite->img_ratio.x / sprite->img_ratio.y * sprite->im.height;
	x = (x_start >= 0 ? x_start : 0);
	while (x < x_start + size.x && x < p->width)
	{
			x_img = (x - x_start) * im_screen_ratio.x;
			y = y_start >= 0 ? y_start : 0;
			while (y < y_start + size.y && y < p->height)
			{
				if (dist < p->dist_array[x][y])
				{
					y_img = (y - y_start) * im_screen_ratio.y;
					if (color_pix_transparency(&p->win_img[p->win_buffered], x, y, *get_pix_address(&sprite->simg->im, x_img, y_img)))
						p->dist_array[x][y] = dist;
				}
				y++;
			}
		x++;
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

int		in_bounds(int val, int max)
{
	return ((0 <= val) && (val < max));
}

int		in_bounds2D(int x, int y, t_map *map)
{
	return ((0 <= x) && (x < map->width) && (0 <= y) && (y < map->height));
}

// TODO multi layers
int		in_bounds3D(int x, int y, int z, t_map *map)
{
	return (in_bounds2D(x, y, map) && (z == 0));
}

double	sqnorm(double x, double y)
{
	return (x * x + y * y);
}

double	sqnorm3D(double x, double y, double z)
{
	return (x * x + y * y + z * z);
}

double	norm(double x, double y)
{
	return (sqrt(x * x + y * y));
}

t_pt2d	add_vec(t_pt2d *v1, t_pt2d *v2)
{
	t_pt2d res;

	res.x = v1->x + v2->x;
	res.y = v1->y + v2->y;
	return (res);
}

t_pt2d pt2d(double x, double y)
{
	t_pt2d res;

	res.x = x;
	res.y = y;
	return (res);
}

t_ipt2d ipt2d(int x, int y)
{
	t_ipt2d res;

	res.x = x;
	res.y = y;
	return (res);
}

int ipt2d_equal(t_ipt2d v1, t_ipt2d v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}