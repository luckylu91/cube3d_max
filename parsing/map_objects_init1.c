/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_objects_init1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:44:06 by lzins             #+#    #+#             */
/*   Updated: 2021/02/20 11:11:27 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "map_objects_init.h"

void		set_theta_pos(t_pack *p, int i, int j)
{
	p->pos.x = i + .5;
	p->pos.y = j + .5;
	if (p->map.grid[i][j] == 'N')
		p->theta = M_PI / 2;
	else if (p->map.grid[i][j] == 'S')
		p->theta = -M_PI / 2;
	if (p->map.grid[i][j] == 'W')
		p->theta = M_PI;
	else if (p->map.grid[i][j] == 'E')
		p->theta = 0;
	p->theta_v = 0;
}

int			addback_sprite(t_list **asprites, t_sprite *new_val)
{
	t_list		*new_elem;

	if (!(new_elem = ft_lstnew(new_val)))
		return (-1);
	ft_lstadd_back(asprites, new_elem);
	return (1);
}

t_sprite	*add_sprite(t_pack *p, int i, int j, char type)
{
	t_sprite	*sprite;

	if (!(sprite = ft_calloc(1, sizeof(t_sprite))))
		return (NULL);
	sprite->type = type;
	sprite->pos.x = i + .5;
	sprite->pos.y = j + .5;
	sprite->path = NULL;
	sprite->previous_block.x = i;
	sprite->previous_block.y = j;
	sprite->simg = sprite_img_from_type(p, type);
	if (addback_sprite(&p->sprites, sprite) == -1)
	{
		free(sprite);
		return (NULL);
	}
	if (ft_strchr(ENEMIES, type)
		&& addback_sprite(&p->enemies, sprite) == -1)
	{
		free(sprite);
		return (NULL);
	}
	return (sprite);
}

static int	add_one_tpblock_exit(t_map *map, t_ipt2d coord, t_ipt2d coord2,
	void *tp_ptr)
{
	t_tpblock *tp;

	tp = (t_tpblock*)tp_ptr;
	if (!is_outside_or_wall(block_at(map, coord2))
			&& block_at(map, coord2) != TELEP)
	{
		tp->exits[tp->n_exits] = cardinal_from_ipt2d(
				ipt2d(coord2.x - tp->x, coord2.y - tp->y));
		tp->n_exits++;
	}
	return (1);
}

void		add_tpblock(t_map *map, t_ipt2d coord, int tp_count)
{
	t_tpblock *tp;

	tp = map->tpblocks + tp_count;
	tp->x = coord.x;
	tp->y = coord.y;
	tp->n_exits = 0;
	iter_four_neighbors(map, coord, tp, &add_one_tpblock_exit);
}
