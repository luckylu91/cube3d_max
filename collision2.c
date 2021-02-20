/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:53:57 by lzins             #+#    #+#             */
/*   Updated: 2021/02/17 09:58:40 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		card_ord(int cardinal)
{
	if (cardinal == WEST)
		return (0);
	else if (cardinal == NORTH)
		return (1);
	else if (cardinal == EAST)
		return (2);
	else
		return (3);
}

static t_pt2d	from_left_right(t_ipt2d coord, int cardinal, double lr_coef)
{
	if (cardinal == WEST)
		return (pt2d(coord.x + 0., coord.y + lr_coef));
	else if (cardinal == NORTH)
		return (pt2d(coord.x + 1 - lr_coef, coord.y + 0.));
	else if (cardinal == EAST)
		return (pt2d(coord.x + 1., coord.y + 1 - lr_coef));
	else
		return (pt2d(coord.x + lr_coef, coord.y + 1.));
}

static void		change_direction(t_pack *p, t_pt2d *movement, int card_in,
	int card_out)
{
	int			delta_card;
	double		theta;

	delta_card = (card_ord(card_out) - card_ord(card_in) + 6) % 4;
	theta = M_PI / 2 * delta_card;
	rotate3d_packdir(p, theta, 0);
	rotate(movement, theta);
}

void			teleport(t_pack *p, t_pt2d movement, t_ipt2d tp_in_coord,
	t_wall hit)
{
	t_tpblock	*tp;
	int			i_dest;
	int			i;
	int			i_exit;
	int			cardinal_out;

	i_dest = rand() % (p->map.n_tpblocks - 1);
	i = -1;
	while (++i < p->map.n_tpblocks)
	{
		tp = p->map.tpblocks + i;
		if (tp->x == tp_in_coord.x && tp->y == tp_in_coord.y)
			i_dest++;
		if (i == i_dest)
			break ;
	}
	i_exit = rand() % tp->n_exits;
	cardinal_out = tp->exits[i_exit];
	p->pos = from_left_right(ipt2d(tp->x, tp->y),
		cardinal_out, 1 - hit.left_right_coef);
	change_direction(p, &movement, hit.cardinal, cardinal_out);
	add_pt2d_ptr(&p->pos, movement);
}

void			move_and_correct(t_pack *p, t_pt2d movement)
{
	t_wall	hit;
	double	hit_dist;
	double	movement_dist;
	t_ipt2d	hit_coord;

	hit_dist = ray_march(&p->pos, &movement, &p->map, &hit);
	hit_coord = ipt2d(hit.hit_x, hit.hit_y);
	movement_dist = norm(movement.x, movement.y);
	if (movement_dist < hit_dist - EPSILON)
		add_pt2d_ptr(&p->pos, movement);
	else if (block_at(&p->map, hit_coord) != TELEP)
		add_pt2d_ptr(
			&p->pos,
			mult_pt2d(movement, (hit_dist - EPSILON) / movement_dist));
	else
	{
		add_pt2d_ptr(&p->pos, mult_pt2d(movement, hit_dist / movement_dist));
		movement = mult_pt2d(
			movement,
			(movement_dist - hit_dist) / movement_dist);
		teleport(p, movement, hit_coord, hit);
	}
	correct_collision(p);
}
