#include "cub3d.h"

static void rotate3d(double dth, double dth_v, t_pack *p)
{
	p->theta += dth;
	p->theta_v += dth_v;
	p->dir.x = cos(p->theta);
	p->dir.y = -sin(p->theta);
	p->dir_ortho.x = sin(p->theta);
	p->dir_ortho.y = cos(p->theta);
	p->dir3d.x = cos(p->theta) * cos(p->theta_v);
	p->dir3d.y = -sin(p->theta) * cos(p->theta_v);
	p->dir3d.z = sin(p->theta_v);
}

static void move(double delta, t_pack *p)
{
	p->pos.x += delta * p->dir.x;
	p->pos.y += delta * p->dir.y;
	p->pos.x += delta * p->dir.x;
	p->pos.y += delta * p->dir.y;
}

static void move_ortho(double delta, t_pack *p)
{
	p->pos.x += delta * p->dir_ortho.x;
	p->pos.y += delta * p->dir_ortho.y;
	p->pos.x += delta * p->dir_ortho.x;
	p->pos.y += delta * p->dir_ortho.y;
}

int motion_hook(int x, int y, t_pack *p)
{
	static int firstcall = 1;
	double deltaX;
	double deltaY;

	if (firstcall)
	{
		mlx_mouse_move(p->win, p->width / 2, p->height / 2);
		firstcall = 0;
		return (0);
	}
	deltaX = x - p->width / 2;
	deltaY = y - p->height / 2;
	rotate3d(-.01 * deltaX, .01 * deltaY, p);
	mlx_mouse_move(p->win, p->width / 2, p->height / 2);
	return (0);
}

int key_press_hook(int kc, t_pack *p)
{
	if (kc == KEY_ESC)
		free_pack_and_quit(p);
	else if (kc == KEY_W)
		p->key_pressed |= KEYMASK_W;
	else if (kc == KEY_A)
		p->key_pressed |= KEYMASK_A;
	else if (kc == KEY_S)
		p->key_pressed |= KEYMASK_S;
	else if  (kc == KEY_D)
		p->key_pressed |= KEYMASK_D;
	else if (kc == KEY_LEFT)
		p->key_pressed |= KEYMASK_LEFT;
	else if  (kc == KEY_RIGHT)
		p->key_pressed |= KEYMASK_RIGHT;
	return (0);
}

int key_release_hook(int kc, t_pack *p)
{
	if (kc == KEY_W)
		p->key_pressed &= ~KEYMASK_W;
	else if (kc == KEY_A)
		p->key_pressed &= ~KEYMASK_A;
	else if (kc == KEY_S)
		p->key_pressed &= ~KEYMASK_S;
	else if  (kc == KEY_D)
		p->key_pressed &= ~KEYMASK_D;
	else if (kc == KEY_LEFT)
		p->key_pressed &= ~KEYMASK_LEFT;
	else if  (kc == KEY_RIGHT)
		p->key_pressed &= ~KEYMASK_RIGHT;
	return (0);
}


void	collect_pea(t_pack *p)
{
	int x;
	int y;

	x = (int)p->pos.x;
	y = (int)p->pos.y;
	if (p->map.pea_sprites_grid[x][y])
	{
		ft_lstremove(&p->sprites, p->map.pea_sprites_grid[x][y], sizeof(t_sprite));
		free_sprite(p->map.pea_sprites_grid[x][y]);
		p->map.pea_sprites_grid[x][y] = NULL;
		p->map.peas_count--;
		//
		printf("remaining peas : %d\n", p->map.peas_count);
	}
}

int	update_path_if_needed(t_pack *p, t_sprite *enemy)
{
	t_list	*path_patch;
	t_ipt2d	*dest;
	t_list	*dead_ghost;

	if ((int)p->pos.x == (int)enemy->pos.x && (int)p->pos.y == (int)enemy->pos.y)
		return (0);
	if (!enemy->path)
	{
		// TODO -> if (() == -1)
		update_shortest_path(&p->map, enemy, ipt2d(p->pos.x, p->pos.y));
		if (!enemy->path)
		{
			ft_printf("A lonely ghost commited suicide... again.\n"); // not necessary stderr. TODO ft_fprintf instead;
			dead_ghost = ft_lstremove(&p->enemies, enemy, sizeof(t_sprite));
			ft_lstremove(&p->sprites, enemy, sizeof(t_sprite));
			ft_lstdelone(dead_ghost, &free_sprite);
			return (0);
		}
	}
	else
	{
		dest = path_destination(enemy->path);
		if (dest->x != (int)p->pos.x || dest->y != (int)p->pos.y)
		{
			// //
			// printf("Player has moved since last lime\n");
			// //
			// ft_lstclear(&enemy->path, &free);
			// TODO optimize....
			update_shortest_path(&p->map, enemy, ipt2d(p->pos.x, p->pos.y));
		}
	}
	return (1);
	// else
	// {
	// 	next_block = *(t_ipt2d*)(*apath)->content;
	// 	if (abs(next_block.x - floor(enemy->pos.x))
	// 			+ abs(next_block.y - floor(enemy->pos.y)) > 1)
	// 	{
	// 		printf("oh oh\n");
	// 		path_patch = shortest_path(&p->map, ipt2d(enemy->pos.x, enemy->pos.y), ipt2d(next_block.x, next_block.y));
	// 		*apath = ft_lstcat(path_patch, );
	// 	}
	// }
}

int move_enemy(t_pack *p, t_sprite *enemy)
{
	double dist;
	double dist_to_block;
	t_ipt2d *next_block;
	t_list	*path;
	int		move_axis;
	int		ret;

	// printf("Moving enemy currently at (%.3f,%.3f)\n", enemy->pos.x, enemy->pos.y);
	/**/ move_axis = 0;
	// uglyyyyyy
	ret = update_path_if_needed(p, enemy);
	if (ret == 0 || ret == -1)
		return (ret);
	if (!enemy->path)
	{
		printf("You DIED !\n");
		return (1);
	}
	// important for first
	// while (ipt2d_equal(*ipt2d_at(enemy->path), enemy->previous_block))
	// 	pop_first(&enemy->path, NULL);
	// ugly because of above
	// if (!enemy->path)
	// 	return;
	dist = p->time_loop * ENEMY_SPEED;
	while (dist > 0.)
	{
		next_block = ipt2d_at(enemy->path);
		if (next_block->x == enemy->previous_block.x /**/ && abs(next_block->y - enemy->previous_block.y) == 1)
		{
			move_axis = 1;
			dist_to_block = fabs(next_block->y + .5 - enemy->pos.y);
		}
		else /**/ if (next_block->y == enemy->previous_block.y /**/ && abs(next_block->x - enemy->previous_block.x) == 1)
		{
			move_axis = 0;
			dist_to_block = fabs(next_block->x + .5 - enemy->pos.x);
		}
		/**/else
		{
			printf("oh oh\n");
			return (-1);
		}
		// //
		// printf("\tdist to next block : %.3f\n", dist_to_block);
		// //
		if (dist < dist_to_block)
		{
			if (move_axis == 0)
				enemy->pos.x += dist * ((enemy->pos.x < next_block->x + .5) ? 1 : -1);
			else
				enemy->pos.y += dist * ((enemy->pos.y < next_block->y + .5) ? 1 : -1);
			dist = 0.;
		}
		else
		{
			enemy->pos.x = next_block->x + .5;
			enemy->pos.y = next_block->y + .5;
			enemy->previous_block.x = next_block->x;
			enemy->previous_block.y = next_block->y;
			dist -= dist_to_block;
			pop_first(&enemy->path, NULL);
			// //
			// printf("Enemy changing block :\n");
			// //
		}
		//
		// printf("\tnew pos (%.3f,%.3f)\n", enemy->pos.x, enemy->pos.y);
	}
	return (1);
}

int	move_all_enemies(t_pack *p)
{
	t_list *enemy_elem;

	enemy_elem = p->enemies;
	while (enemy_elem)
	{
		if (move_enemy(p, sprite_at(enemy_elem)) == -1)
			return (-1);
		enemy_elem = enemy_elem->next;
	}
	return (1);
}

int loop_hook(t_pack *p)
{
	double rotation;
	double translation;
	double translation_ortho;

	//
	printf("elapsed : %f\n", p->time_total);
	rotation = .05 * (
		(p->key_pressed & KEYMASK_LEFT ? 1 : 0)
		+ (p->key_pressed & KEYMASK_RIGHT ? -1 : 0)
	);
	translation = .1 * (
		(p->key_pressed & KEYMASK_W ? 1 : 0)
		+ (p->key_pressed & KEYMASK_S ? -1 : 0)
	);
	translation_ortho = .1 * (
		(p->key_pressed & KEYMASK_D ? 1 : 0)
		+ (p->key_pressed & KEYMASK_A ? -1 : 0)
	);
	if (translation)
		move(translation, p);
	if (translation_ortho)
		move_ortho(translation_ortho, p);
	if (rotation)
		rotate3d(rotation, .0, p);
	if (translation || translation_ortho)
		correct_collision(p);
	collect_pea(p);
	if (move_all_enemies(p) == -1)
		free_pack_and_quit(p);
	render(p);
	render_minimap(p);
	swap(p);
	tick(p);
	return (0);
}