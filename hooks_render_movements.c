/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_render_movements.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:36:08 by lzins             #+#    #+#             */
/*   Updated: 2021/02/18 15:51:39 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement_vector(t_pack *p, double t, double t_ortho, t_pt2d *mvt)
{
	if (t)
		*mvt = mult_pt2d(p->dir, t);
	if (t_ortho)
		add_pt2d_ptr(mvt, mult_pt2d(p->dir_ortho, t_ortho));
	if (t && t_ortho)
		*mvt = mult_pt2d(*mvt, 1 / sqrt(2));
}

void		handle_movement(t_pack *p)
{
	double	rotation;
	double	translation;
	double	translation_ortho;
	t_pt2d	movement;

	ft_bzero(&movement, sizeof(t_pt2d));
	rotation = .2 * (
		(p->key_pressed & KEYMASK_LEFT ? 1 : 0)
		+ (p->key_pressed & KEYMASK_RIGHT ? -1 : 0));
	translation = PLAYER_SPEED * p->time_loop * (
		(p->key_pressed & KEYMASK_W ? 1 : 0)
		+ (p->key_pressed & KEYMASK_S ? -1 : 0));
	translation_ortho = PLAYER_SPEED * p->time_loop * (
		(p->key_pressed & KEYMASK_D ? 1 : 0)
		+ (p->key_pressed & KEYMASK_A ? -1 : 0));
	if (translation || translation_ortho)
	{
		movement_vector(p, translation, translation_ortho, &movement);
		move_and_correct(p, movement);
	}
	if (rotation)
		rotate3d_packdir(p, rotation, .0);
}
