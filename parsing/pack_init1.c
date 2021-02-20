/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 17:20:51 by lzins             #+#    #+#             */
/*   Updated: 2021/02/11 18:03:46 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int			init_sprites(t_pack *p)
{
	int		i;
	size_t	n_sprites;

	n_sprites = ft_strlen(SPRITES);
	if (!(p->sprite_images = ft_calloc(n_sprites, sizeof(t_sprite_img))))
		return (-1);
	i = -1;
	while (++i < ft_strlen(SPRITES))
	{
		if (load_sprite_image(p, SPRITES[i], &p->sprite_images[i]) == -1)
			return (-1);
	}
	return (1);
}

int			set_win_elements(t_pack *p)
{
	void	*img1;
	void	*img2;

	img1 = mlx_new_image(p->mlx, p->width, p->height);
	img2 = mlx_new_image(p->mlx, p->width, p->height);
	p->win = mlx_new_window(p->mlx, p->width, p->height, "Cub3D");
	p->win_img[0] = img_from_ptr(img1, p->width, p->height);
	p->win_img[1] = img_from_ptr(img2, p->width, p->height);
	if (!p->win || !img1 || !img2)
		return (win_image_error(p));
	p->win_buffered = 0;
	p->key_pressed = 0;
	return (1);
}

int			load_const_imgs(t_pack *p)
{
	void *start_menu_img;

	if (load_image(p, "start_menu.xpm", &p->start_screen) == -1)
		return (-1);
	if (load_image(p, "win_menu.xpm", &p->victory_screen) == -1)
		return (-1);
	if (load_image(p, "lose_menu.xpm", &p->lose_screen) == -1)
		return (-1);
	if (load_image(p, "heart.xpm", &p->heart_img) == -1)
		return (-1);
	if (load_image(p, "heart_empty.xpm", &p->heart_empty_img) == -1)
		return (-1);
	if (load_image(p, "portal.xpm", &p->portal_img) == -1)
		return (-1);
	return (1);
}
