#include "cub3d.h"

void	correct_collision(t_pack *p)
{
	int x1, x2, y1, y2;
	int xa, ya;
	double new_pos_x, new_pos_y;
	int pos_x_int;
	int pos_y_int;
	int adjacent_wall;
	double norm_corner;

	pos_x_int = floor(p->pos.x);
	pos_y_int = floor(p->pos.y);
	if (!in_bounds2D(pos_x_int, pos_y_int, &p->map) || p->map.grid[pos_x_int][pos_y_int] == WALL)
		return ;
	x1 = floor(p->pos.x - COLLISION_RADIUS);
	x2 = floor(p->pos.x + COLLISION_RADIUS);
	xa = pos_x_int == x1 ? x2 : x1; // not used whenever x1 == x2
	y1 = floor(p->pos.y - COLLISION_RADIUS);
	y2 = floor(p->pos.y + COLLISION_RADIUS);
	ya = pos_y_int == y1 ? y2 : y1;

	if (x1 != x2 && p->map.grid[xa][pos_y_int] == WALL)
		p->pos.x = (pos_x_int == x1 ? x2 - COLLISION_RADIUS : x2 + COLLISION_RADIUS);
	if (y1 != y2 && p->map.grid[pos_x_int][ya] == WALL)
		p->pos.y = (pos_y_int == y1 ? y2 - COLLISION_RADIUS : y2 + COLLISION_RADIUS);
	if (x1 != x2 && y1 != y2 && p->map.grid[xa][pos_y_int] != WALL && p->map.grid[pos_x_int][ya] != WALL && p->map.grid[xa][ya] == WALL)
	{
		norm_corner = norm(p->pos.x - x2, p->pos.y - y2);
		p->pos.x = x2 + COLLISION_RADIUS * (p->pos.x - x2) / norm_corner;
		p->pos.y = y2 + COLLISION_RADIUS * (p->pos.y - y2) / norm_corner;
	}
	p->pos3d.x = p->pos.x;
	p->pos3d.y = p->pos.y;
}

// void correct_collision(t_pack *p)
// {
// 	t_pt2d	dist_vect;
// 	int		collision;
// 	double	dist;

// 	collision = collision_vector(p->pos, p->dir, p->map, &dist_vect);
// 	if (collision == -1)
// 		return ;
// 	if (collision == 1)
// 	{
// 		printf("Collision : distx = %.2f | disty = %.2f \n", dist_vect.x, dist_vect.y);
// 		printf("Collision (before): posx = %.2f | posy = %.2f\n",p->pos->x, p->pos->y);
// 		fflush(stdout);
// 		dist = norm(dist_vect.x, dist_vect.y);
// 		p->pos->x += (COLLISION_RADIUS - fabs(dist_vect.x)) * dist_vect.x / dist;
// 		p->pos->y += (COLLISION_RADIUS - fabs(dist_vect.y)) * dist_vect.y / dist;
// 		printf("Collision (after): posx = %.2f | posy = %.2f\n\n", p->pos->x, p->pos->y);
// 		fflush(stdout);
// 	}
// }