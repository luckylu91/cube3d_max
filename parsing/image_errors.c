/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:03:52 by lzins             #+#    #+#             */
/*   Updated: 2021/02/10 17:33:50 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	load_sprite_error(t_pack *p)
{
	int i;

	i = -1;
	while (++i < ft_strlen(SPRITES))
		free_img(p->mlx, &p->sprite_images[i].im);
	return (message_error("Error while loading sprites images"));
}

int	win_image_error(t_pack *p)
{
	if (p->win_img[0].img)
		mlx_destroy_image(p->mlx, p->win_img[0].img);
	if (p->win_img[1].img)
		mlx_destroy_image(p->mlx, p->win_img[1].img);
	return (message_error("Error while creating window-related images"));
}

int	load_cubeface_error(t_pack *p, int i)
{
	ft_printf("Error\n");
	ft_printf("Error while loading cube-face-sprite num. %d\n", i);
	while (--i >= 0)
		mlx_destroy_image(p->mlx, p->cube_faces[i].img);
	return (-1);
}
