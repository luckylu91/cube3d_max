/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:04:35 by lzins             #+#    #+#             */
/*   Updated: 2021/02/10 17:25:25 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int		colored_image(void *mlx, int color, t_img *res)
{
	void *img;

	if (!(img = mlx_new_image(mlx, 1, 1)))
		return (-1);
	*res = img_from_ptr(img, 1, 1);
	color_pix(res, 0, 0, color);
	return (1);
}

int		funky_image(t_pack *p, t_img *im)
{
	void	*img;
	int		x;
	int		y;

	if (!(img = mlx_new_image(p->mlx, 256, 256)))
		return (-1);
	*im = img_from_ptr(img, 256, 256);
	x = -1;
	while (++x < 256)
	{
		y = -1;
		while (++y < 256)
			color_pix(im, x, y, (x << 16) + y);
	}
	return (1);
}
