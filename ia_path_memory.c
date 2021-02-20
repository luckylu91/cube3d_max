/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia_path_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:58:56 by lzins             #+#    #+#             */
/*   Updated: 2021/02/19 19:54:18 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		path_copy(t_path *src, t_path *res)
{
	return (ft_lstcpy(src->steps, &res->steps, sizeof(t_ipt2d)));
}

void	clear_path(t_path *path)
{
	ft_lstclear(&path->steps, free);
	path->steps = NULL;
}

void	clear_path_grid(t_map *map, t_path **pathgrid)
{
	int x;
	int y;

	x = -1;
	while (++x < map->width)
	{
		y = -1;
		while (++y < map->height)
			clear_path(&pathgrid[x][y]);
		free(pathgrid[x]);
	}
	free(pathgrid);
}

int	free_all_error(t_map *map, t_path **pathgrid, t_list **visit_fifo)
{
	ft_printf("Error\n");
	ft_printf("Malloc error in update_shortest_path\n");
	clear_path_grid(map, pathgrid);
	ft_lstclear(visit_fifo, free);
	return (0);
}
