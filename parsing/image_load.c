/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:09:57 by lzins             #+#    #+#             */
/*   Updated: 2021/02/11 17:23:01 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	load_dot_image(t_pack *p, t_sprite_img *res)
{
	void	*img;
	t_img	im;
	int		w;
	int		h;

	if (!(img = mlx_xpm_file_to_image(p->mlx, "dot.xpm", &w, &h)))
		return (file_not_found_error("dot.xpm"));
	im = img_from_ptr(img, w, h);
	res->im = im;
	res->img_ratio.x = .2;
	res->img_ratio.y = .2;
	res->img_offset.x = 0.;
	res->img_offset.y = 0.;
	return (1);
}

static int	load_ghost_image(t_pack *p, t_sprite_img *res)
{
	void	*img;
	t_img	im;
	int		w;
	int		h;

	if (!(img = mlx_xpm_file_to_image(p->mlx, p->sprite_fname, &w, &h)))
		return (file_not_found_error(p->sprite_fname));
	im = img_from_ptr(img, w, h);
	res->im = im;
	res->img_ratio.x = 1;
	res->img_ratio.y = 1;
	res->img_offset.x = 0.;
	res->img_offset.y = 0.;
	return (1);
}

int			load_sprite_image(t_pack *p, int type, t_sprite_img *res)
{
	if (type == PEA && load_dot_image(p, res) == -1)
		return (file_not_found_error("dot.xpm"));
	if (type == GHOST && load_ghost_image(p, res) == -1)
		return (file_not_found_error(p->sprite_fname));
	return (1);
}
