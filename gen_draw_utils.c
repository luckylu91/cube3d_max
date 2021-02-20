/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_draw_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:35:30 by lzins             #+#    #+#             */
/*   Updated: 2021/02/17 13:45:24 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rect_image(t_img *win_im, t_img *im, t_ipt2d origin, int width)
{
	t_ipt2d	win_coord;
	t_ipt2d	im_coord;
	int		height;
	double	ratio;

	height = width * im->height / im->width;
	ratio = im->width / (double)width;
	win_coord.x = origin.x - 1;
	while (++win_coord.x < origin.x + width)
	{
		im_coord.x = ratio * (win_coord.x - origin.x);
		win_coord.y = origin.y - 1;
		while (++win_coord.y < origin.y + height)
		{
			im_coord.y = ratio * (win_coord.y - origin.y);
			color_pix_transparency(
				win_im,
				win_coord.x, win_coord.y,
				*get_pix_address(im, im_coord.x, im_coord.y));
		}
	}
}

void	draw_menu_image(t_pack *p, t_img *menu_im)
{
	double	menu_hwratio;
	double	win_hwratio;
	t_ipt2d	origin;
	int		width;

	menu_hwratio = menu_im->height / (double)menu_im->width;
	win_hwratio = p->height / (double)p->width;
	if (menu_hwratio > win_hwratio)
	{
		origin.y = 0;
		width = p->height * menu_im->width / menu_im->height;
		origin.x = (p->width - width) / 2;
	}
	else
	{
		origin.x = 0;
		origin.y = (
			p->height - p->width * menu_im->height / menu_im->width) / 2;
		width = p->width;
	}
	clear_image(buff_img(p));
	draw_rect_image(buff_img(p), menu_im, origin, width);
}
