/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:00:30 by lzins             #+#    #+#             */
/*   Updated: 2021/02/10 16:00:46 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_img(void *mlx, t_img *im)
{
	if (im->img)
		mlx_destroy_image(mlx, im->img);
	ft_bzero(im, sizeof(t_img));
}

void	free_sprite(void *sprite_ptr)
{
	t_sprite *sprite;

	sprite = (t_sprite*)sprite_ptr;
	ft_lstclear(&sprite->path, &free);
	free(sprite);
}

void	free_win(void *mlx, void *win)
{
	if (win)
		mlx_destroy_window(mlx, win);
}

void	free_map(t_map *map)
{
	int i;
	int j;

	i = -1;
	while (++i < map->width)
	{
		free(map->grid[i]);
		free(map->pea_sprites_grid[i]);
		j = -1;
		while (++j < map->height)
			ft_lstclear(&map->neighbors[i][j], &free);
		free(map->neighbors[i]);
	}
	free(map->grid);
	free(map->pea_sprites_grid);
	free(map->neighbors);
	free(map->tpblocks);
}
