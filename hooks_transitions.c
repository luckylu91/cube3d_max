/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_transitions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:47:07 by lzins             #+#    #+#             */
/*   Updated: 2021/02/19 10:23:23 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		start_menu(t_pack *p)
{
	mlx_hook(p->win, 2, 1L << 0, &key_press_hook_menu, p);
	mlx_loop_hook(p->mlx, &loop_hook_menu, p);
	p->redraw_fun = &put_start_screen;
}

void		start_game(t_pack *p)
{
	mlx_hook(p->win, 2, 1L << 0, &key_press_hook, p);
	mlx_hook(p->win, 3, 1L << 1, &key_release_hook, p);
	if (p->mouse_on)
	{
		mlx_mouse_hide();
		mlx_hook(p->win, 6, 1L << 6, &motion_hook, p);
	}
	mlx_loop_hook(p->mlx, &loop_hook, p);
	reset_clock(p);
	p->redraw_fun = &draw;
}

void		end_game(t_pack *p)
{
	mlx_hook(p->win, 3, 1L << 1, &nothing_hook, p);
	if (p->mouse_on)
	{
		mlx_mouse_show();
		mlx_hook(p->win, 6, 1L << 6, &nothing_hook, NULL);
	}
	mlx_hook(p->win, 2, 1L << 0, &key_press_hook_end, p);
	mlx_loop_hook(p->mlx, &loop_hook_end, p);
	p->redraw_fun = &put_end_screen;
	p->time_restart = TIME_RESTART;
	reset_clock(p);
}

static void	do_nothing(void *content)
{
	return ;
}

void		restart_game(t_pack *p)
{
	ft_lstclear(&p->sprites, &free_sprite);
	ft_lstclear(&p->enemies, &do_nothing);
	set_pack_map_properties_re(p);
	p->lives = p->lives_max;
	p->key_pressed = 0;
	start_menu(p);
}
