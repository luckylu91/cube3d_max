/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:49:44 by lzins             #+#    #+#             */
/*   Updated: 2021/02/17 09:58:12 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	adjust_pos(t_pack *p, t_ipt2d c1, t_ipt2d c2, t_ipt2d ca)
{
	t_ipt2d	pos_int;
	double	norm_corner;

	pos_int = round_pt2d(p->pos);
	if (c1.x != c2.x && p->map.grid[ca.x][pos_int.y] == WALL)
		p->pos.x = (pos_int.x == c1.x ?
			c2.x - COLLISION_RADIUS : c2.x + COLLISION_RADIUS);
	if (c1.y != c2.y && p->map.grid[pos_int.x][ca.y] == WALL)
		p->pos.y = (pos_int.y == c1.y ?
			c2.y - COLLISION_RADIUS : c2.y + COLLISION_RADIUS);
	if (c1.x != c2.x && c1.y != c2.y
			&& p->map.grid[ca.x][pos_int.y] != WALL
			&& p->map.grid[pos_int.x][ca.y] != WALL
			&& p->map.grid[ca.x][ca.y] == WALL)
	{
		norm_corner = norm(p->pos.x - c2.x, p->pos.y - c2.y);
		p->pos.x = c2.x
			+ COLLISION_RADIUS * (p->pos.x - c2.x) / norm_corner;
		p->pos.y = c2.y
			+ COLLISION_RADIUS * (p->pos.y - c2.y) / norm_corner;
	}
	p->pos3d.x = p->pos.x;
	p->pos3d.y = p->pos.y;
}

void		correct_collision(t_pack *p)
{
	t_ipt2d	coord1;
	t_ipt2d	coord2;
	t_ipt2d	coorda;
	t_ipt2d pos_int;

	pos_int = round_pt2d(p->pos);
	if (!in_bounds2D(pos_int.x, pos_int.y, &p->map)
			|| p->map.grid[pos_int.x][pos_int.y] == WALL)
		return ;
	coord1.x = floor(p->pos.x - COLLISION_RADIUS);
	coord2.x = floor(p->pos.x + COLLISION_RADIUS);
	coorda.x = pos_int.x == coord1.x ? coord2.x : coord1.x;
	coord1.y = floor(p->pos.y - COLLISION_RADIUS);
	coord2.y = floor(p->pos.y + COLLISION_RADIUS);
	coorda.y = pos_int.y == coord1.y ? coord2.y : coord1.y;
	adjust_pos(p, coord1, coord2, coorda);
}
