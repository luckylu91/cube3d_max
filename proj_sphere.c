#include "cub3d.h"
#define SPHERE_RADIUS .1

static inline void difference(t_pt2d *A, t_pt2d *B, t_pt2d *AB)
{
	AB->x = B->x - A->x;
	AB->y = B->y - A->y;
}

static inline double dot(t_pt2d *u, t_pt2d *v)
{
	return (u->x * v->x + u->y * v->y);
}
// (approx)
void sphere_proj(t_pack *p, t_pt2d *sphere_pos)
{
	t_pt2d OC;
	double dist_ortho;
	double screen_radius;
	double screen_x;

	difference(&p->pos, sphere_pos, &OC);
	dist_ortho = dot(&OC, &p->dir);
	screen_radius = SPHERE_RADIUS * SCREEN_DIST / dist_ortho;
	screen_x = 
}