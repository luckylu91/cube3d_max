/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:46:48 by lzins             #+#    #+#             */
/*   Updated: 2021/02/17 13:47:01 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_start_screen(t_pack *p)
{
	draw_menu_image(p, &p->start_screen);
	mlx_put_image_to_window(p->mlx, p->win, buff_img(p)->img, 0, 0);
	swap(p);
}

int		key_press_hook_menu(int kc, t_pack *p)
{
	if (kc == KEY_ESC)
		free_pack_and_quit(p);
	else
		start_game(p);
	return (0);
}

int		loop_hook_menu(t_pack *p)
{
	put_start_screen(p);
	return (0);
}
