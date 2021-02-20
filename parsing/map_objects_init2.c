/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_objects_init2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:45:51 by lzins             #+#    #+#             */
/*   Updated: 2021/02/11 17:20:22 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "map_objects_init.h"

static void	complete_dir_pos(t_pack *p)
{
	p->dir.x = cos(p->theta);
	p->dir.y = -sin(p->theta);
	p->dir3d.x = cos(p->theta);
	p->dir3d.y = -sin(p->theta);
	p->dir3d.z = 0.;
	p->pos3d.x = p->pos.x;
	p->pos3d.y = p->pos.y;
	p->pos3d.z = 0.5;
	p->dir_ortho.x = sin(p->theta);
	p->dir_ortho.y = cos(p->theta);
}

static int	count_tpblocks(t_map *map)
{
	int	i;
	int	j;
	int	n_tpblocks;

	n_tpblocks = 0;
	i = -1;
	while (++i < map->width)
	{
		j = -1;
		while (++j < map->height)
		{
			if (map->grid[i][j] == TELEP)
				n_tpblocks++;
		}
	}
	return (n_tpblocks);
}

int			set_pack_map_properties_re_one(t_pack *p, int i, int j)
{
	t_sprite	*pea_sprite;

	if (ft_strchr("NSWE", p->map.grid[i][j]))
		set_theta_pos(p, i, j);
	else
	{
		if (p->map.grid[i][j] == GHOST && !add_sprite(p, i, j, GHOST))
			return (load_sprite_error(p));
		if (!is_blocking(i, j, &p->map) && p->map.grid[i][j] != OUTSIDE)
		{
			if (!(pea_sprite = add_sprite(p, i, j, PEA)))
				return (load_sprite_error(p));
			p->map.pea_sprites_grid[i][j] = pea_sprite;
			p->map.peas_count++;
		}
	}
	return (1);
}

int			set_pack_map_properties_re(t_pack *p)
{
	int			i;
	int			j;
	int			tp_count;

	p->map.peas_count = 0;
	i = -1;
	while (++i < p->map.width)
	{
		j = -1;
		while (++j < p->map.height)
			if (set_pack_map_properties_re_one(p, i, j) == -1)
				return (-1);
	}
	complete_dir_pos(p);
	return (1);
}

int			set_pack_map_properties_first(t_pack *p)
{
	t_ipt2d		coord;
	t_sprite	*pea_sprite;
	int			tp_count;

	p->map.n_tpblocks = count_tpblocks(&p->map);
	if (!(p->map.tpblocks = ft_calloc(p->map.n_tpblocks, sizeof(t_tpblock))))
		return (map_error());
	tp_count = 0;
	coord.x = -1;
	while (++coord.x < p->map.width)
	{
		coord.y = -1;
		while (++coord.y < p->map.height)
		{
			if (block_at(&p->map, coord) == TELEP)
				add_tpblock(&p->map, coord, tp_count++);
		}
	}
	if (set_pack_map_properties_re(p) == -1)
		return (-1);
	return (1);
}
