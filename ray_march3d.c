#include "cub3d.h"

#define MAP_HEIGHT 1

double	ray_march3D_x(t_pt3d *pos, t_pt3d *dir, t_map *map, t_wall *hit)
{
	static int		x_index;
	static int		x_incr;
	static double	y;
	static double	z;
	static double	dy;
	static double	dz;
	
	x_incr = dir->x > 0. ? 1 : -1;
	x_index = dir->x > 0. ? (int)ceil(pos->x) : (int)floor(pos->x);
	hit->cardinal = dir->x > 0. ? WEST : EAST;
	dy = x_incr * dir->y / dir->x;
	dz = x_incr * dir->z / dir->x;
	if (dir->x != 0.)
	{
		y = pos->y + ((double)x_index - pos->x) * dir->y / dir->x;
		z = pos->z + ((double)x_index - pos->x) * dir->z / dir->x;
		// printf("x_index start : %d", x_index);
		// printf("y start : %.2f\n", y);
		// printf("z start : %.2f\n", z);
		// printf("x_index + (x_incr - 1) / 2 = %d\n", x_index + (x_incr - 1) / 2);
		// printf("(int)floor(y) = %d\n", (int)floor(y));
		// printf("(int)floor(z) = %d\n", (int)floor(z));
		while (in_bounds3D(x_index + (x_incr - 1) / 2, (int)floor(y), (int)floor(z), map))
		{
			if (map->grid[x_index + (x_incr - 1) / 2][(int)floor(y)] == WALL)
			{
				hit->up_down_coef = z - floor(z);
				hit->left_right_coef = y - floor(y);
				if (dir->x < 0.)
					hit->left_right_coef = 1 - hit->left_right_coef;
				hit->hit_x = x_index;
				hit->hit_y = y;
				hit->hit_z = z;
				return (sqnorm3D(x_index - pos->x, y - pos->y, z - pos->z));
			}
			// y += x_incr * dir->y / dir->x;
			// z += x_incr * dir->z / dir->x;
			y += dy;
			z += dz;
			x_index += x_incr;
			// printf("x_index : %d", x_index);
			// printf("y start : %.2f\n", y);
			// printf("z start : %.2f\n", z);
			// printf("x_index + (x_incr - 1) / 2 = %d\n", x_index + (x_incr - 1) / 2);
			// printf("(int)floor(y) = %d\n", (int)floor(y));
			// printf("(int)floor(z) = %d\n", (int)floor(z));
		}
	}
	return (-1.);
}

double	ray_march3D_y(t_pt3d *pos, t_pt3d *dir, t_map *map, t_wall *hit)
{
	static double	x;
	static int		y_index;
	static int		y_incr;
	static double	z;
	static double	dx;
	static double	dz;
	
	y_incr = dir->y > 0. ? 1 : -1;
	y_index = dir->y > 0. ? (int)ceil(pos->y) : (int)floor(pos->y);
	hit->cardinal = dir->y > 0. ? NORTH : SOUTH;
	dx = y_incr * dir->x / dir->y;
	dz = y_incr * dir->z / dir->y;
	if (dir->y != 0.)
	{
		x = pos->x + ((double)y_index - pos->y) * dir->x / dir->y;
		z = pos->z + ((double)y_index - pos->y) * dir->z / dir->y;
		while (in_bounds3D((int)floor(x), y_index + (y_incr - 1) / 2, (int)floor(z), map))
		{
			if (map->grid[(int)floor(x)][y_index + (y_incr - 1) / 2] == WALL)
			{
				hit->up_down_coef = z - floor(z);
				hit->left_right_coef = 1 - (x - floor(x));
				if (dir->y < 0.)
					hit->left_right_coef = 1 - hit->left_right_coef;
				hit->hit_x = x;
				hit->hit_y = y_index;
				hit->hit_z = z;
				return (sqnorm3D(x - pos->x, y_index - pos->y, z - pos->z));
			}
			// x += y_incr * dir->x / dir->y;
			// z += y_incr * dir->z / dir->y;
			x += dx;
			z += dz;
			y_index += y_incr;
		}
	}
	return (-1.);
}

// floor at 0, ceil at 1
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
	if (in_bounds2D((int)floor(x), (int)floor(y), map))
	{
		hit->left_right_coef = x - floor(x);
		hit->up_down_coef = y - floor(y); // o pif
		hit->hit_x = x;
		hit->hit_y = y;
		hit->hit_z = z_index;
		return (sqnorm3D(x - pos->x, y - pos->y, z_index - pos->z));
	}
	return (-1.);
}

int		index_of_minimum(double *array, int len)
{
	int		i;
	int		i_min;
	double	min;

	i_min = -1;
	i = -1;
	min = -1.;
	while (++i < len)
	{
		if (array[i] >= 0.)
		{
			if (min == -1. || array[i] < min)
			{
				min = array[i];
				i_min = i;
			}
		}
	}
	return (i_min);
}

double ray_march3D(t_pt3d *pos, t_pt3d *dir, t_map *map, t_wall *hit)
{
	static t_wall	hits[3];
	static double	dists[3];
	static int		i_min;
	
	dists[0] = ray_march3D_x(pos, dir, map, &hits[0]);
	dists[1] = ray_march3D_y(pos, dir, map, &hits[1]);
	dists[2] = ray_march3D_z(pos, dir, map, &hits[2]);
	i_min = index_of_minimum(dists, 3);
	if (i_min == -1)
		return (-1.);
	*hit = hits[i_min];
	return (dists[i_min]);
	// *hit = hits[0];
	// return (dists[0]);
}

static inline void div_ptr2(t_pt3d *dest, t_pt3d *a, double b)
{
	dest->x = a->x / b;
	dest->y = a->y / b;
	dest->z = a->z / b;
}

void new_ray_march3D(t_pt3d *pos, t_pt3d *dir, t_map *map, t_wall *hit)
{
	t_pt3d deltas[3];
	double dists[3];

	div_ptr2(deltas, dir, fabs(dir->x));
	div_ptr2(deltas + 1, dir, fabs(dir->y));
	div_ptr2(deltas + 2, dir, fabs(dir->z));
}