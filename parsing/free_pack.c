/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:00:57 by lzins             #+#    #+#             */
/*   Updated: 2021/02/10 17:53:31 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_arrays(t_pack *p)
{
	int i;

	i = -1;
	while (++i < 6)
	{
		free_img(p->mlx, &p->cube_faces[i]);
		free(p->cube_faces_fnames[i]);
	}
	if (p->sprite_images)
	{
		i = -1;
		while (++i < ft_strlen(SPRITES))
			free_img(p->mlx, &p->sprite_images[i].im);
		free(p->sprite_images);
	}
}

int			free_pack(t_pack *p)
{
	free_img(p->mlx, &p->win_img[0]);
	free_img(p->mlx, &p->win_img[1]);
	free_img(p->mlx, &p->portal_img);
	free_img(p->mlx, &p->heart_img);
	free_img(p->mlx, &p->heart_empty_img);
	clear_arrays(p);
	free(p->sprite_fname);
	ft_lstclear(&p->sprites, &free_sprite);
	ft_arrayclear((void**)p->dist_array, p->width);
	free_map(&p->map);
	free_win(p->mlx, p->win);
	return (-1);
}

int			free_pack_and_quit(t_pack *p)
{
	free_pack(p);
	exit(0);
	return (0);
}
