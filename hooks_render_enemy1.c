/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_render_enemy1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:31:45 by lzins             #+#    #+#             */
/*   Updated: 2021/02/20 10:30:36 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_next_block_dist(t_sprite *enemy, t_ipt2d *next_block,
	double *dist_to_block)
{
	*next_block = *ipt2d_at(enemy->path);
	if (next_block->x == enemy->previous_block.x)
		*dist_to_block = fabs(next_block->y + .5 - enemy->pos.y);
	else if (next_block->y == enemy->previous_block.y)
		*dist_to_block = fabs(next_block->x + .5 - enemy->pos.x);
}

static void	move_toward_block(t_sprite *enemy, double dist, t_ipt2d next_block)
{
	if (next_block.x == enemy->previous_block.x)
		enemy->pos.y += dist * ((enemy->pos.y < next_block.y + .5) ? 1 : -1);
	else
		enemy->pos.x += dist * ((enemy->pos.x < next_block.x + .5) ? 1 : -1);
}

static void	move_to_block(t_pack *p, t_sprite *enemy, t_ipt2d next_block)
{
	t_ipt2d block_tp_dest;

	if (is_tpblock(next_block, &p->map)
			&& enemy->path->next
			&& is_tpblock(*ipt2d_at(enemy->path->next), &p->map))
	{
		// printf("jumping tp ");
		// printf("(moving to (%d,%d), so tp to (%d,%d)\n", ipt2d_at(enemy->path)->x, ipt2d_at(enemy->path)->y, ipt2d_at(enemy->path->next)->x, ipt2d_at(enemy->path->next)->y);
		pop_first(&enemy->path, NULL);
		pop_first(&enemy->path, &block_tp_dest);
		enemy->previous_block = block_tp_dest;
		enemy->pos = pt2d(block_tp_dest.x + .5, block_tp_dest.y + .5);
	}
	else
	{
		// printf("popping (%d, %d)\n", ipt2d_at(enemy->path)->x, ipt2d_at(enemy->path)->y);
		pop_first(&enemy->path, NULL);
		enemy->pos = pt2d(next_block.x + .5, next_block.y + .5);
		enemy->previous_block = next_block;
	}
}

static int	move_enemy(t_pack *p, t_sprite *enemy)
{
	double	dist;
	double	dist_to_block;
	t_ipt2d	next_block;
	int		ret;

	// ///
	// printf("eney coord (%4.2f,%4.2f)\n", enemy->pos.x, enemy->pos.y);
	// t_pt2d pos1 = enemy->pos;
	// ///
	ret = update_path_if_needed(p, enemy);
	if (ret == 0 || ret == -1)
		return (ret);
	dist = p->time_loop * ENEMY_SPEED;
	while (dist > 0. && enemy->path)
	{
		get_next_block_dist(enemy, &next_block, &dist_to_block);
		if (dist < dist_to_block)
		{
			// printf("move toward | ");
			// printf("dist = %4.2f, dist_to_block = %4.2f\n", dist, dist_to_block);
			move_toward_block(enemy, dist, next_block);
			dist = 0.;
		}
		else
		{
			// printf("move to block (%d,%d) | ", next_block.x, next_block.y);
			// printf("dist = %4.2f, dist_to_block = %4.2f\n", dist, dist_to_block);
			move_to_block(p, enemy, next_block);
			dist -= dist_to_block;
		}
	}
	// ///
	// double jmp = norm(pos1.x - enemy->pos.x, pos1.y - enemy->pos.y);
	// printf("enemy jumped a distance of %4.2f\n", jmp);
	// ///
	return (1);
}

int			move_all_enemies(t_pack *p)
{
	t_list		*enemy_elem;
	t_sprite	*enemy;

	// ////
	// if (is_tpblock(round_pt2d(p->pos), &p->map))
	// 	printf("player on tpblock\n");
	// ////
	enemy_elem = p->enemies;
	while (enemy_elem)
	{
		enemy = sprite_at(enemy_elem);
		if (move_enemy(p, enemy) == -1)
			return (-1);
		if (ipt2d_equal(round_pt2d(p->pos), round_pt2d(enemy->pos)))
			p->touched_by_enemy = 1;
		enemy_elem = enemy_elem->next;
	}
	return (1);
}
