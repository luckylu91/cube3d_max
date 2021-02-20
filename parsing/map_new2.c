/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_new2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:06:21 by lzins             #+#    #+#             */
/*   Updated: 2021/02/20 10:20:30 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "map_new.h"

static int	add_neighbor(t_map *map, t_ipt2d coord, t_ipt2d val)
{
	if (!add_back_ipt2d_once(&map->neighbors[coord.x][coord.y], val))
		return (0);
	return (1);
}

static int	add_tp_blocks(t_map *map, t_ipt2d coord)
{
	int			i_tp;
	t_tpblock	*tp;

	i_tp = -1;
	while (++i_tp < map->n_tpblocks)
	{
		tp = &map->tpblocks[i_tp];
		if (!add_neighbor(map, coord, ipt2d(tp->x, tp->y)))
			return (0);
	}
	return (1);
}

static int	find_neighbors(t_map *map, t_ipt2d coord)
{
	t_ipt2d	coord2;
	int		axis;
	int		offset;

	axis = -1;
	while (++axis < 2)
	{
		offset = -1;
		while (offset < 2)
		{
			coord2.x = coord.x + (axis == 0 ? offset : 0);
			coord2.y = coord.y + (axis == 1 ? offset : 0);
			if (!is_outside_or_wall(block_at(map, coord2))
					&& !add_neighbor(map, coord, coord2))
				return (0);
			offset += 2;
		}
	}
	if (block_at(map, coord) == TELEP && !add_tp_blocks(map, coord))
		return (0);
	return (1);
}

static int	init_map_neighbors(t_map *map)
{
	t_ipt2d coord;

	coord.x = -1;
	while (++coord.x < map->width)
	{
		coord.y = -1;
		while (++coord.y < map->height)
			if (!is_outside_or_wall(block_at(map, coord))
					&& !find_neighbors(map, coord))
				return (0);
	}
	return (1);
}

int			new_map(t_list *map_lst, t_pack *p)
{
	char	**grid;
	int		height;
	int		width;
	t_ipt2d	start_stop;

	map_dimentions(map_lst, &start_stop.x, &start_stop.y);
	// printf("map dimentions : (%d, %d)\n", start_stop.x, start_stop.y);
	height = ft_lstsize(map_lst);
	width = start_stop.y - start_stop.x + 1;
	if (!(p->map.grid = (char**)ft_array(width, height, sizeof(char))))
		return (map_error());
	if (!(p->map.pea_sprites_grid = (t_sprite***)\
			ft_array(width, height, sizeof(t_sprite*))))
		return (map_error());
	if (!(p->map.neighbors = (t_list***)\
			ft_array(width, height, sizeof(t_list*))))
		return (map_error());
	p->map.width = width;
	p->map.height = height;
	fill_map_grid(map_lst, &p->map, start_stop.x, start_stop.y);
	if (map_check(&p->map) == -1
			|| set_pack_map_properties_first(p) == -1
			|| !init_map_neighbors(&p->map))
		return (-1);
	return (1);
}
