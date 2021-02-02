#include "cub3d.h"

static void set_dist_column(t_pack *p, int x, double dist)
{
	int y;

	y = -1;
	while (++y < p->height)
		p->dist_array[x][y] = dist;
}

static void	render_rays(t_pack *p)
{
	int		i;
	t_pt2d	ray_dir;
	double	screen_x;
	double	dist;
	t_wall	hit;
	double	dist_ortho;
	int		visible_height;

	i = -p->width / 2 - 1;
	while (++i < (p->width + 1) / 2)
	{
		screen_x = (double)i / (double)p->width * SCREEN_WIDTH_SIZE;
		ray_dir.x = p->dir.x * SCREEN_DIST + screen_x * (-p->dir.y);
		ray_dir.y = p->dir.y * SCREEN_DIST + screen_x * p->dir.x;
		if ((dist = ray_march(&p->pos, &ray_dir, &p->map, &hit)) >= 0.)
		{
			set_dist_column(p, i + p->width / 2, dist);
			dist_ortho = SCREEN_DIST * dist / norm(SCREEN_DIST, fabs(screen_x));
			visible_height = WALL_SIZE * SCREEN_DIST / dist_ortho * p->width / SCREEN_WIDTH_SIZE;
			rays_updown(p, &ray_dir, i + p->width / 2, visible_height);
			col_fill(p, &hit, i + p->width / 2, visible_height);
		}
	}
}

// do a lst_iter
static void	render_sprites(t_pack *p)
{
	double	left;
	double	left_screen;
	double	dist;
	double	dist_ortho;
	int		x_start;
	int		size_screen;
	t_list	*sp_lst;

	sp_lst = p->sprites;
	while (sp_lst)
	{
		dist = (sprite_at(sp_lst)->pos.x - p->pos.x) * p->dir.x + (sprite_at(sp_lst)->pos.y - p->pos.y) * p->dir.y;
		if (dist < SCREEN_DIST)
		{
			sp_lst = sp_lst->next;
			continue;
		}
		dist_ortho = (sprite_at(sp_lst)->pos.x - p->pos.x) * -p->dir.y + (sprite_at(sp_lst)->pos.y - p->pos.y) * p->dir.x;
		if (fabs(dist_ortho / dist) > (SCREEN_WIDTH_SIZE + WALL_SIZE) / (2 * SCREEN_DIST))
		{
			sp_lst = sp_lst->next;
			continue;
		}
		left = WALL_SIZE / 2 - dist_ortho;
		left_screen = left / dist * SCREEN_DIST * p->width;
		x_start = p->width / 2 - left_screen;
		size_screen = WALL_SIZE / dist * SCREEN_DIST * p->width;
		sprite_fill(p, sprite_at(sp_lst), x_start, size_screen, dist);
		sp_lst = sp_lst->next;
	}
}

void render(t_pack *p)
{
	clear_image(&p->win_img[p->win_buffered]);
	render_rays(p);
	render_sprites(p);
}