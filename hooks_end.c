/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:40:05 by lzins             #+#    #+#             */
/*   Updated: 2021/02/17 13:46:02 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_end_screen(t_pack *p)
{
	if (p->you_won)
		draw_menu_image(p, &p->victory_screen);
	else
		draw_menu_image(p, &p->lose_screen);
	mlx_put_image_to_window(p->mlx, p->win, buff_img(p)->img, 0, 0);
	swap(p);
}

int		key_press_hook_end(int kc, t_pack *p)
{
	if (kc == KEY_ESC)
		free_pack_and_quit(p);
	else if (p->time_restart == 0.)
		restart_game(p);
	return (0);
}

int		loop_hook_end(t_pack *p)
{
	tick(p);
	if (p->time_restart > 0.)
		p->time_restart = fmax(0., p->time_restart - p->time_loop);
	put_end_screen(p);
	return (0);
}
