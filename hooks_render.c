/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:50:42 by lzins             #+#    #+#             */
/*   Updated: 2021/02/20 10:31:03 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	motion_hook(int x, int y, t_pack *p)
{
	static int	firstcall = 1;
	double		delta_x;
	double		delta_y;

	if (firstcall)
	{
		mlx_mouse_move(p->win, p->width / 2, p->height / 2);
		firstcall = 0;
		return (0);
	}
	delta_x = x - p->width / 2;
	delta_y = y - p->height / 2;
	rotate3d_packdir(p, -.01 * delta_x, .01 * delta_y);
	mlx_mouse_move(p->win, p->width / 2, p->height / 2);
	return (0);
}

int	key_press_hook(int kc, t_pack *p)
{
	if (kc == KEY_ESC)
		free_pack_and_quit(p);
	else if (kc == KEY_W)
		p->key_pressed |= KEYMASK_W;
	else if (kc == KEY_A)
		p->key_pressed |= KEYMASK_A;
	else if (kc == KEY_S)
		p->key_pressed |= KEYMASK_S;
	else if (kc == KEY_D)
		p->key_pressed |= KEYMASK_D;
	else if (kc == KEY_LEFT)
		p->key_pressed |= KEYMASK_LEFT;
	else if (kc == KEY_RIGHT)
		p->key_pressed |= KEYMASK_RIGHT;
	return (0);
}

int	key_release_hook(int kc, t_pack *p)
{
	if (kc == KEY_W)
		p->key_pressed &= ~KEYMASK_W;
	else if (kc == KEY_A)
		p->key_pressed &= ~KEYMASK_A;
	else if (kc == KEY_S)
		p->key_pressed &= ~KEYMASK_S;
	else if (kc == KEY_D)
		p->key_pressed &= ~KEYMASK_D;
	else if (kc == KEY_LEFT)
		p->key_pressed &= ~KEYMASK_LEFT;
	else if (kc == KEY_RIGHT)
		p->key_pressed &= ~KEYMASK_RIGHT;
	return (0);
}

int	expose_hook(t_pack *p)
{
	p->redraw_fun(p);
	return (0);
}

int	loop_hook(t_pack *p)
{
	// printf("--------------------\n");
	handle_movement(p);
	collect_pea(p);
	if (p->game_on && move_all_enemies(p) == -1)
		free_pack_and_quit(p);
	assess_victory(p);
	assess_life(p);
	draw(p);
	tick(p);
	return (0);
}
