#include "cub3d.h"

static double	ray_march_x(t_pt2d *pos, t_pt2d *dir, t_map *map, t_wall *hit)
{
	int		x_index;
	int		x_incr;
	double	y;
	
	x_incr = dir->x > 0. ? 1 : -1;
	x_index = dir->x > 0. ? (int)ceil(pos->x) : (int)floor(pos->x);
	hit->cardinal = dir->x > 0. ? WEST : EAST;
	if (dir->x != 0.)
	{
		y = pos->y + ((double)x_index - pos->x) * dir->y / dir->x;
		while (in_bounds2D(x_index + (x_incr - 1) / 2, (int)floor(y), map))
		{
			if (map->grid[x_index + (x_incr - 1) / 2][(int)floor(y)] == WALL)
			{
				hit->left_right_coef = y - floor(y);
				if (dir->x < 0.)
					hit->left_right_coef = 1 - hit->left_right_coef;
				hit->hit_x = x_index;
				hit->hit_y = y;
				return (norm(x_index - pos->x, y - pos->y));
			}
			y += x_incr * dir->y / dir->x;
			x_index += x_incr;
		}
	}
	return (-1.);
}

static double	ray_march_y(t_pt2d *pos, t_pt2d *dir, t_map *map, t_wall *hit)
{
	double	x;
	int		y_index;
	int		y_incr;
	
	y_incr = dir->y > 0. ? 1 : -1;
	y_index = dir->y > 0. ? (int)ceil(pos->y) : (int)floor(pos->y);
	hit->cardinal = dir->y > 0. ? NORTH : SOUTH;
	if (dir->y != 0.)
	{
		x = pos->x + ((double)y_index - pos->y) * dir->x / dir->y;
		while (in_bounds2D((int)floor(x), y_index + (y_incr - 1) / 2, map))
		{
			if (map->grid[(int)floor(x)][y_index + (y_incr - 1) / 2] == WALL)
			{
				hit->left_right_coef = 1 - (x - floor(x));
				if (dir->y < 0.)
					hit->left_right_coef = 1 - hit->left_right_coef;
				hit->hit_x = x;
				hit->hit_y = y_index;
				return (norm(x - pos->x, y_index - pos->y));
			}
			x += y_incr * dir->x / dir->y;
			y_index += y_incr;
		}
	}
	return (-1.);
}

double ray_march(t_pt2d *pos, t_pt2d *dir, t_map *map, t_wall *hit)
{
	t_wall	hitx;
	t_wall	hity;
	double	distx;
	double	disty;

	distx = ray_march_x(pos, dir, map, &hitx);
	disty = ray_march_y(pos, dir, map, &hity);
	if ((distx >= 0.) && ((distx <= disty) || (disty < 0.)))
	{
		*hit = hitx;
		return (distx);
	}
	if ((disty >= 0.) && ((disty <= distx) || (distx < 0.)))
	{
		*hit = hity;
		return (disty);
	}
	return (-1.);
}

double ray_march3D_z(t_pt3d *pos, t_pt3d *dir, t_map *map, t_wall *hit)
{
	static double x;
	static double y;
	static int z_index;

	if (dir->z == 0)
		return (-1.);
	z_index = dir->z > 0. ? 1 : 0;
	hit->cardinal = dir->z > 0. ? CEIL : FLOOR;
	x = pos->x + (z_index - pos->z) * dir->x / dir->z;
	y = pos->y + (z_index - pos->z) * dir->y / dir->z;
	hit->left_right_coef = x - floor(x);
	hit->up_down_coef = y - floor(y);
	return (sqnorm3D(x - pos->x, y - pos->y, z_index - pos->z));
}